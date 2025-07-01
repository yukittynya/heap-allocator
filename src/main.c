#include "heap.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    int* a = heap_alloc(sizeof(a));
    int* b = heap_alloc(sizeof(b));
    *a = 9;
    *b = 12;

    int* c = malloc(sizeof(int));
    *c = 25;

    print_chunks();
}
