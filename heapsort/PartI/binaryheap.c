#include "binaryheap.h"
#include <assert.h>
#include <string.h>


/*allocate memory in the heap for a node_heap type element and returns a pointer to the new node_heap*/

node_heap *allocate_node_heap(void) {
    node_heap *node = malloc(sizeof(node_heap));
    return node;
}

/*initialise the heap array elements*/

void initial_heap(node_heap **heap, char *sequence) {
    char *iter = sequence;
    int i = 1;
    while (*iter) {
        heap[i] = allocate_node_heap();
        heap[i]->key = iter;
        heap[i]->position = i;
        i++;
        iter++;
    }
}


/*print every element of the heap array*/
void print_elem_heap(node_heap **heap, int length) {
    int i;
    for (i = 1; i <= length; i++) {
        printf("%c ", *heap[i]->key);
    }
    printf("\n");
    for (i = 1; i <= length; i++) {
        printf("%d ", heap[i]->position);
    }
    printf("\n");
}

/* returns the index in the heap array where the parent is allocated for the index passed as argument*/

int parent(int index) {
    return index / 2;
}

/* returns the index in the heap array where the left child is allocated for the index passed as argument*/

int left_child(int index) {
    return 2 * index;
}

/* returns the index in the heap array where the right child is allocated for the index passed as argument*/

int right_child(int index) {
    return 2 * index + 1;
}

/* exchange node_heap node1 to node_heap node2*/

void swap(node_heap *node1, node_heap *node2) {
    char *auxc = node2->key;
    int auxi = node2->position;
    node2->key = node1->key;
    node2->position = node1->position;
    node1->key = auxc;
    node1->position = auxi;
}

int getLargestChild(node_heap **heap, int current, int heap_size) {
    if (current > heap_size)
        return 0;
    int left = getLargestChild(heap, left_child(current), heap_size);
    int right = getLargestChild(heap, right_child(current), heap_size);
    if (!left) {
        if (!right) {
            return current;
        }
        return heap[right]->key[0] > heap[current]->key[0] ? right : current;
    }
    if (!right) {
        return heap[left]->key[0] > heap[current]->key[0] ? left : current;
    }
    left = heap[left]->key[0] > heap[right]->key[0] ? left : right;
    return heap[left]->key[0] > heap[current]->key[0] ? left : current;
}

/*Moves down the value of the heap[current] so the subtree rooted at index "current" satisfies with the max-heap property*/

void max_heapify(node_heap **heap, int current, int heap_size) {
    int largestChild = getLargestChild(heap, current, heap_size);
    if (largestChild != current) {
        swap(heap[largestChild], heap[current]);
        max_heapify(heap, largestChild, heap_size);
    }
}

/*it orders the heap so the ordered heap complies the max-heap property*/

void build_max_heap(node_heap **heap, int heap_size) {
    int i;
    for (i = heap_size / 2; i >= 1; i--) {
        max_heapify(heap, i, heap_size);
    }
}

/*starting from a max-heap ordered array, it moves the largest item from the heap and it into the array position left as the heap shrinks*/

void heapsort(node_heap **heap, int length) {
    build_max_heap(heap, length);
    int i;
    for (i = length; i > 1; i--) {
        swap(heap[i], heap[1]);
        max_heapify(heap, 1, i - 1);
    }

}

/*free the memory allocated by a node_heap type element in the heap*/

void free_node(node_heap *node) {
    free(node);
}

/*free the memory allocated in the heap array*/

void free_heap(node_heap **heap, int length) {
    int i;
    for (i = 1; i <= length; i++) {
        free_node(heap[i]);
    }
}