#ifndef HEAP_H
#define HEAP_H 

#include <stdlib.h>
#include <stdbool.h>

typedef struct heapchunk {
    struct heapchunk* next;
    size_t size;
} heapchunk;

void* heap_alloc(size_t size);
void heap_free(void* chunk);

void print_chunks();

#endif // !HEAP_H #define HEAP_H
