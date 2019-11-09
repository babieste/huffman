
#include <stdlib.h>
#include <stdio.h>

#include "heap.h"

/**
 * A utility function allocate a new min heap node 
 * with given character and frequency of the character
*/
HeapNode *new_node(char data, unsigned int freq)
{
    HeapNode *temp = (HeapNode *)malloc(sizeof(HeapNode));

    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}

/**
 * A utility function to create a min heap of given capacity
*/
MinHeap *create_min_heap(unsigned capacity)
{
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));

    // current size is 0
    minHeap->size = 0;

    minHeap->capacity = capacity;

    minHeap->array = (HeapNode **)malloc(minHeap->capacity * sizeof(HeapNode *));
    return minHeap;
}

/**
 * A utility function to swap two min heap nodes
*/
void swap_min_heap_node(HeapNode **a, HeapNode **b)
{
    HeapNode *t = *a;
    *a = *b;
    *b = t;
}

void heapify(MinHeap *minHeap, int index)
{

    int smallest = index;
    unsigned int left = 2 * index + 1;
    unsigned int right = 2 * index + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != index)
    {
        swap_min_heap_node(&minHeap->array[smallest],
                           &minHeap->array[index]);
        heapify(minHeap, smallest);
    }
}

/**
 * Utility function to check the end of the iterations 
 * when building the huffman tree
*/
bool size_one(MinHeap *minHeap)
{
    return (minHeap->size == 1);
}

/**
 * Extract the node from min_heap with the lowest value
 * Used when building huffman tree and fusing two different values
 * into one
 * 
*/
HeapNode *extract_min(MinHeap *min_heap)
{

    HeapNode *temp = min_heap->array[0];
    min_heap->array[0] = min_heap->array[min_heap->size - 1];

    --min_heap->size;
    heapify(min_heap, 0);

    return temp;
}

void insert_heap(MinHeap *min_heap, HeapNode *node)
{
    ++min_heap->size;
    int i = min_heap->size - 1;

    while (i && node->freq < min_heap->array[(i - 1) / 2]->freq)
    {

        min_heap->array[i] = min_heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    min_heap->array[i] = node;
}

void build_min_heap(MinHeap *min_heap)
{

    int n = min_heap->size - 1;

    for (int i = (n - 1) / 2; i >= 0; --i)
    {
        heapify(min_heap, i);
    }
}

// A utility function to print an array of size n
void print_array(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%d", arr[i]);
    }

    printf("\n");
}

// Utility function to check if this node is leaf
bool is_leaf(HeapNode *root)
{
    return !(root->left) && !(root->right);
}

/**
 * Creates a min heap of capacity equal to size and inserts 
 * all character of data[] in min heap. Initially size of 
 * min heap is equal to capacity
*/
MinHeap *create_and_build_min_heap(char data[], int freq[], int size)
{

    MinHeap *minHeap = create_min_heap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = new_node(data[i], freq[i]);

    minHeap->size = size;
    build_min_heap(minHeap);

    return minHeap;
}