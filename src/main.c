#include "heap.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    atexit(heap_cleanup);

    int* a = heap_alloc(sizeof(int));
    int* b = heap_alloc(sizeof(b));
    *a = 1213;
    *b = 12;

    print_chunks();

    heap_free(a);

    printf("\n*********After Free********\n");

    print_chunks();

    heap_free(b);
}
