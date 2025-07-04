#ifndef HEAP_H
#define HEAP_H 

#include <stdlib.h>
#include <stdbool.h>

typedef struct heapchunk {
    struct heapchunk* next;
    size_t size;
} heapchunk;

size_t align_chunk(size_t size);

void* heap_alloc(size_t size);
void heap_free(void* chunk);

void add_to_list(heapchunk** head, heapchunk* target);
void remove_from_list(heapchunk** head, heapchunk* target);

heapchunk* split_chunk(heapchunk* target, size_t size);
void coalesce_list();

heapchunk* find_next(heapchunk* target);
heapchunk* find_previous(heapchunk* target);

void heap_cleanup(); 

void print_chunks();
void print_free_list();

#endif // !HEAP_H #define HEAP_H
