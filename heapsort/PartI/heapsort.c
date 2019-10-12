#include "binaryheap.h"
#include <assert.h>
#include <string.h>


int main(int argc, char **argv) {
    assert (argc >= 1);
    int length = strlen(argv[1]);
    node_heap **heap = malloc(sizeof(node_heap*) * (length + 1));
    initial_heap(heap, argv[1]);
    print_elem_heap(heap, length);
    build_max_heap(heap, length);
    print_elem_heap(heap, length);
    heapsort(heap, length);
    print_elem_heap(heap, length);
    free_heap(heap, length);
    free(heap);
    return EXIT_SUCCESS;
}