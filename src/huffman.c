#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stringutils.h"
#include "heap.h"
#include "huffman.h"

// The main function that builds Huffman tree
HeapNode *build_huffman_tree(char *data, int *freq, int size)
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

/**
 * Initialize the structure in order to store a 
 * list of huffman code for each character
 * 
*/
HuffmanCode **init_code(int size)
{
    HuffmanCode **code = (HuffmanCode **)malloc(sizeof(HuffmanCode *) * size);
    if (code == NULL)
    {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++)
    {
        HuffmanCode *char_code = (HuffmanCode *) malloc (sizeof(HuffmanCode));
        if (char_code == NULL){
            exit(EXIT_FAILURE);
        }

        //just some random values to fill in the space
        char_code->code = "0";
        char_code->character = '0';

        code[i] = char_code;
    }

    return code;
}

/**
 * Retrieve the values from the root node, traversing the tree
*/
void traverse_huffman_tree(
    HeapNode *root, char *current_code, 
    HuffmanCode **code, int *current_char)
{
    char *left = "0";
    char *right = "1";

    // Assign 0 to left edge and recur
    if (root->left)
    {
        char *new_current_code = concat(current_code, left);
        traverse_huffman_tree(root->left, new_current_code, code, current_char);
    }

    // Assign 1 to right edge and recur
    if (root->right)
    {
        char *new_current_code = concat(current_code, right);
        traverse_huffman_tree(root->right, new_current_code, code, current_char);
    }

    // If this is a leaf node, then
    // it contains one of the input
    // characters, print the character
    // and its code from arr[]
    if (is_leaf(root))
    {
        code[*current_char]->character = root->data;
        code[*current_char]->code = current_code;

        (*current_char)++;
    }
}

/**
 * Builds the huffman tree and print the codes by 
 * traversing the built huffman tree
 **/
HuffmanCode **huffman_code(char *data, int *freq, int size)
{
    // Construct Huffman Tree
    HeapNode *root = build_huffman_tree(data, freq, size);

    HuffmanCode **result_code = init_code(size);

    int current_char = 0;
    char *initial_char = "";

    traverse_huffman_tree(root, initial_char, result_code, &current_char);

    return result_code;
}

void free_huffman_code (HuffmanCode ** code, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(code[i]->code);
        free(code[i]);
    }

    free(code);
}