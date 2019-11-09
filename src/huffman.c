#include <stdlib.h>
#include <stdio.h>

#include "heap.h"
#include "huffman.h"

// The main function that builds Huffman tree
HeapNode *build_huffman_tree(char data[], int freq[], int size)
{
    HeapNode *left, *right, *top;

    // Step 1: Create a min heap of capacity
    // equal to size.  Initially, there are
    // modes equal to size.
    MinHeap *minHeap = create_and_build_min_heap(data, freq, size);

    // Iterate while size of heap doesn't become 1
    while (!size_one(minHeap))
    {

        // Step 2: Extract the two minimum
        // freq items from min heap
        left = extract_min(minHeap);
        right = extract_min(minHeap);

        // Step 3:  Create a new internal
        // node with frequency equal to the
        // sum of the two nodes frequencies.
        // Make the two extracted node as
        // left and right children of this new node.
        // Add this node to the min heap
        // '$' is a special value for internal nodes, not used
        top = new_node('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insert_heap(minHeap, top);
    }

    // Step 4: The remaining node is the
    // root node and the tree is complete.
    return extract_min(minHeap);
}

// Prints huffman codes from the root of Huffman Tree.
// It uses arr[] to store codes
void print_code(HeapNode *root, int arr[], int top)

{
    // Assign 0 to left edge and recur
    if (root->left)
    {
        arr[top] = 0;
        print_code(root->left, arr, top + 1);
    }

    // Assign 1 to right edge and recur
    if (root->right)
    {
        arr[top] = 1;
        print_code(root->right, arr, top + 1);
    }

    // If this is a leaf node, then
    // it contains one of the input
    // characters, print the character
    // and its code from arr[]
    if (is_leaf(root))
    {
        printf("%c: ", root->data);
        print_array(arr, top);
    }
}

// The main function that builds a
// Huffman Tree and print codes by traversing
// the built Huffman Tree
void huffman_code(char data[], int freq[], int size)
{
    // Construct Huffman Tree
    HeapNode *root = build_huffman_tree(data, freq, size);

    // Print Huffman codes using
    // the Huffman tree built above
    int arr[MAX_TREE_HT], top = 0;

    print_code(root, arr, top);
}