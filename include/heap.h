#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <stdbool.h>

// A Huffman tree node
typedef struct HeapNode
{
    char data;
    unsigned int freq;
    struct HeapNode *left, *right;
} HeapNode;

// A Min Heap:  Collection of
// min-heap (or Huffman tree) nodes
typedef struct
{
    unsigned int size;
    unsigned int capacity;
    struct HeapNode **array;
} MinHeap;

HeapNode *new_node(char data, unsigned int freq);
MinHeap *create_min_heap(unsigned capacity);
void swap_min_heap_node(HeapNode **a, HeapNode **b);
void heapify(MinHeap *min_heap, int idx);
bool size_one(MinHeap *min_heap);
HeapNode *extract_min(MinHeap *min_heap);
void insert_heap(MinHeap *min_heap, HeapNode *node);
void build_min_heap(MinHeap *min_heap);
bool is_leaf(HeapNode *root);
MinHeap *create_and_build_min_heap(char data[], int freq[], int size);
void print_array(int arr[], int n);

#endif