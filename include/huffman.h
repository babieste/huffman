#ifndef HUFFMAN_H
#define HUFFMAN_H

// This constant can be avoided by explicitly
// calculating height of Huffman Tree
#define MAX_TREE_HT 100

struct MinHeapNode *buildHuffmanTree(char data[], int freq[], int size);
void printCodes(struct MinHeapNode *root, int arr[], int top);
void HuffmanCodes(char data[], int freq[], int size);

#endif