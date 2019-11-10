#ifndef HUFFMAN_H
#define HUFFMAN_H

// This constant can be avoided by explicitly
// calculating height of Huffman Tree
#define MAX_TREE_HT 100

typedef struct
{
    char *code;
    char character;
} HuffmanCode;

HeapNode *build_huffman_tree(char *data, int *freq, int size);

HuffmanCode **init_code(int size);

void traverse_huffman_tree(
    HeapNode *root, char *current_code, 
    HuffmanCode **code, int *current_char);

HuffmanCode **huffman_code(char *data, int *freq, int size);

void free_huffman_code (HuffmanCode ** code, int size);

#endif