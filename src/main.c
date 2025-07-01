#include "heap.h"

#include <stdint.h>

int main(int argc, char *argv[]) {
    int* a = heap_alloc(sizeof(int));
    int* b = heap_alloc(sizeof(b));
    *a = 1213;
    *b = 12;

    print_chunks();
}
