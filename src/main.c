#include "heap.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    atexit(heap_cleanup);

    printf("*****Split chunk testing*****\n\n");
    printf("Creating large chunk to be split\n");
    void* large = heap_alloc(100);
    print_chunks();
    heap_free(large);

    printf("\nSplitting chunk\n");
    void* a = heap_alloc(10);
    void* b = heap_alloc(10);

    *(int*)a = 33;
    *(int*)b = 99;

    printf("a: %d\n", *(int*) a);
    printf("b: %d\n", *(int*) b);

    print_chunks();
    print_free_list();
}
