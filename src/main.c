#include "heap.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    atexit(heap_cleanup);

    printf("***** Split chunk testing *****\n\n");
    printf("Creating large chunk to be split\n");
    void* large = heap_alloc(100);
    *(int*)large = 982374592;
    print_chunks();
    heap_free(large);

    printf("\n\n***** Free List After Freeing LARGE *****\n\n");
    print_free_list();

    printf("\nSplitting Chunk and Creating A and B\n");
    void* a = heap_alloc(sizeof(int));
    void* b = heap_alloc(sizeof(int));

    *(int*)a = 33;
    *(int*)b = 99;

    printf("\na: %d, size: %zu\n", *(int*) a, sizeof(a));
    printf("\nb: %d\n", *(int*) b);

    print_chunks();

    heap_free(a);
    heap_free(b);
    printf("\n\n***** Free List After Freeing A And B *****\n\n");
    print_free_list();
}
