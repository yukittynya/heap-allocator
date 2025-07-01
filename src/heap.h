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

void print_chunks();

#endif // !HEAP_H #define HEAP_H
