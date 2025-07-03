/*
*
*   #include <sys/mman.h>
*
*   void *mmap(void *address, size_t length, int protect, int flags, int filedes,off_t offset)
*
*   https://www.delftstack.com/howto/c/use-mmap-function-to-write-to-the-memory-in-c/
*
*   8 byte alignment   
*
*/

#include "heap.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

static heapchunk* allocated_head = NULL;
static heapchunk* free_head = NULL;

inline size_t align_chunk(size_t size) {
    return (size + 7) & ~7;
}

void* heap_alloc(size_t size) {
    size_t aligned_size = align_chunk(size);     

    heapchunk* current = free_head;

    while (current != NULL) {
        if (current -> size == aligned_size + sizeof(heapchunk)) {
            remove_from_list(&free_head, current);
            add_to_list(&allocated_head, current);

            return (char*) current + sizeof(heapchunk);
        }

        if (current -> size >= aligned_size + sizeof(heapchunk)) {
            remove_from_list(&free_head, current);

            heapchunk* new_chunk = split_chunk(current, aligned_size + sizeof(heapchunk));

            new_chunk -> next = NULL;

            add_to_list(&free_head, new_chunk);

            add_to_list(&allocated_head, current);

            return (char*) current + sizeof(heapchunk);
        }

        current = current -> next;
    }

    heapchunk* new_chunk = mmap(NULL, aligned_size + sizeof(heapchunk), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0); 

    if (new_chunk == MAP_FAILED) {
        return NULL;
    }

    new_chunk -> size = aligned_size + sizeof(heapchunk);
    new_chunk -> next = NULL;

    add_to_list(&allocated_head, new_chunk);

    return (char*) new_chunk + sizeof(heapchunk);
}

void heap_free(void* ptr) {
    if (ptr == NULL) return;

    heapchunk* target = (heapchunk*) ((char*) ptr - sizeof(heapchunk));

    remove_from_list(&allocated_head, target);
    add_to_list(&free_head, target);

    coalease_list();
}

void add_to_list(heapchunk** head, heapchunk* target) {
    if (*head == NULL) {
        *head = target;
    } else {
        target -> next = *head;
        *head = target;
    }
}

void remove_from_list(heapchunk** head, heapchunk* target) {
    heapchunk* previous = NULL;
    heapchunk* current = *head;

    while (current != NULL && current != target) {
        previous = current;
        current = current -> next;
    }

    if (current == target) {
        if (previous == NULL) {
            *head = current -> next;
        } else {
            previous -> next = current -> next;
        }
    }
} 

heapchunk* split_chunk(heapchunk* target, size_t size) {
    heapchunk* chunk;

    chunk = (heapchunk*) ((char*) target + size);
    chunk -> size = target -> size - size;

    target -> size = size;

    return chunk;
}

void coalease_list() {
    heapchunk* current = free_head;

    while (current != NULL) {
        heapchunk* next_node = current -> next;

        heapchunk* prev = find_previous(current);
        heapchunk* next = find_next(current);

        if (prev != NULL || next != NULL) {
            remove_from_list(&free_head, current);

            if (prev != NULL) remove_from_list(&free_head, prev);
            if (next != NULL) remove_from_list(&free_head, next);

            heapchunk* result = prev ? prev : current;

            result -> size = (prev ? prev -> size : 0) + current -> size + (next ? next -> size : 0); 

            add_to_list(&free_head, result);
        }

        current = next_node;
    }
} 

heapchunk* find_next(heapchunk* target) {
    void* next_addr = (char*) target + target -> size; 

    heapchunk* current = free_head;

    while (current != NULL) {
        if ((char*) current == next_addr) {
            return current;
        } 

        current = current -> next;
    }

    return NULL;
} 

heapchunk* find_previous(heapchunk* target) {
    heapchunk* current = free_head;

    while (current != NULL) {
        if ((char*) current + current -> size == (char*) target) {
            return current;
        }

        current = current -> next;
    }
    
    return NULL;
}

void heap_cleanup() {
    heapchunk* current = free_head;

    while (current != NULL) {
        heapchunk* next = current -> next;
        munmap(current, current -> size);
        current = next;
    }

    free_head = NULL;

    current = allocated_head;

    while (current != NULL) {
        heapchunk* next = current -> next;
        munmap(current, current -> size);
        current = next;
    }

    allocated_head = NULL;
} 

void print_chunks() {
    heapchunk* ptr = allocated_head;
    int count = 0;

    while (ptr != NULL) {
        int value = *(int*) ((char*) ptr + sizeof(heapchunk));

        printf("\nChunk %d\n", count++);
        printf("    Pointer: %p\n", ptr);
        printf("    Size: %zu bytes\n", ptr -> size);
        printf("    Value: %d\n", value);

        ptr = ptr -> next;
    }
}

void print_free_list() {
    heapchunk* ptr = free_head;
    int count = 0;

    printf("\n\n*****Free List*****\n\n");

    while (ptr != NULL) {
        int value = *(int*) ((char*) ptr + sizeof(heapchunk));

        printf("\nChunk %d\n", count++);
        printf("    Pointer: %p\n", ptr);
        printf("    Size: %zu bytes\n", ptr -> size);
        printf("    Value: %d\n", value);

        ptr = ptr -> next;
    }
}
