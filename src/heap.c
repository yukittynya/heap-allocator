/*
*
* #include <sys/mman.h>
*
* void *mmap(void *address, size_t length, int protect, int flags, int filedes,off_t offset)
*
* https://www.delftstack.com/howto/c/use-mmap-function-to-write-to-the-memory-in-c/
*
*/

#include "heap.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

static heapchunk* head = NULL;

void* heap_alloc(size_t size) {
    heapchunk* new_chunk = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0); 

    if (new_chunk == MAP_FAILED) {
        return NULL;
    }

    new_chunk -> size = size + sizeof(heapchunk);
    new_chunk -> next = NULL;

    if (head == NULL) {
        head = new_chunk;
    } else {
        heapchunk* current = head;

        while (current -> next != NULL) {
            current = current -> next;
        }

        current -> next = new_chunk;
    }

    return (char*) new_chunk + sizeof(heapchunk);
}

void heap_free(void* chunk) {
}

void print_chunks() {
    heapchunk* ptr = head;
    int count = 0;

    while (ptr != NULL) {
        printf("\nChunk %d\n", count++);
        printf("    Pointer: %p\n", ptr);
        printf("    Size: %zu\n", ptr -> size);

        ptr = ptr -> next;
    }
}
