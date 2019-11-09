#ifndef HUFFMAN_H
#define HUFFMAN_H

// This constant can be avoided by explicitly
// calculating height of Huffman Tree
#define MAX_TREE_HT 100

HeapNode *build_huffman_tree(char data[], int freq[], int size);
void print_code(HeapNode *root, int arr[], int top);
void huffman_code(char data[], int freq[], int size);

#endif