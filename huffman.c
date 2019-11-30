#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <float.h>

#define ALPHABET "abcdefghijklmnopqrstuvwxyz"
#define ALPHABET_LENGTH 26

/*
	This struct represents each character in the frequency table
*/
typedef struct
{
    char character;
    int char_counter;
} node;

/*
	This struct represents each node in the Huffman tree
*/
typedef struct huffmanNode
{
    char character;
    int frequency;
    bool enabled; /*used to indicate wether a node has been removed when extracting the min node*/
    struct huffmanNode *left;
    struct huffmanNode *right;
} huffmanNode;

/*
	This struct represents the Huffman tree
*/
typedef struct
{
    int size;
    huffmanNode **array;
} huffmanTree;

void display_frequency_table(node table[])
{
    int i;
    for (i = 0; i < ALPHABET_LENGTH; i++)
    {
        printf("\n--------");
        printf("\nchar \"%c\" - char_counter = %d", table[i].character, table[i].char_counter);
    }
}

void display_huffman_nodes(huffmanNode *array[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("\n-------");
        if (array[i]->frequency == -1)
            printf("\nZERO!");
        printf("\nchar \"%c\" - frequency = %d", array[i]->character, array[i]->frequency);
    }
}

huffmanNode *create_huffman_node(char character, float frequency)
{

    huffmanNode *huffNode = malloc(sizeof(huffmanNode));

    huffNode->character = character;
    huffNode->frequency = frequency;
    huffNode->left = NULL;
    huffNode->right = NULL;
    huffNode->enabled = true;

    return huffNode;
}

/**
 * Returns null if there no more nodes enabled, 
 * or if the array is of size 1, i.e., if there is no 
 * more nodes to extract from tree
 * 
*/
huffmanNode *extract_min(huffmanTree *tree)
{

    if (tree->size == 0)
        return NULL; //avoids null pointers in case size is 0

    int i;
    float minFrequency = FLT_MAX;
    huffmanNode *huffMinNode = NULL;

    for (i = 0; i < tree->size; i++)
    {
        huffmanNode *current = tree->array[i];
        if (current->frequency < minFrequency && current->enabled)
        {
            huffMinNode = tree->array[i];
            minFrequency = huffMinNode->frequency;
        }
    }

    if (huffMinNode == NULL)
        return NULL; //no more nodes to extract

    //disabling for next interation, this node will be
    //used when "fusing" the next node on huffman tree
    huffMinNode->enabled = false;
    return huffMinNode;
}

/*
    Initializes a frequency table with all the alphabet characters
    and it's counters to 0
*/
void init_frequency_table(node table[])
{
    int i;
    for (i = 0; i < ALPHABET_LENGTH; i++)
    {
        table[i].character = ALPHABET[i];
        table[i].char_counter = 0;
    }
}

/*
    Reads the given file and updates the character table with each
    alphabet character occurence and frequency.
*/
void read_file(FILE *file, node table[])
{
    char c;
    int i, letter_counter;

    fseek(file, 0, SEEK_SET);

    letter_counter = 0;
    while ((c = fgetc(file)) != EOF)
    {
        if (c != ' ' && c != '.' && c != '\n')
        {
            c = tolower(c);
            letter_counter = letter_counter + 1;

            for (i = 0; i < ALPHABET_LENGTH; i++)
            {
                if (c == table[i].character)
                    table[i].char_counter = table[i].char_counter + 1;
                
            }
        }
    }
}

/**
 * For memory cleaning purposes
 * Cleaning each node from the array 
 * and the tree structure as well
 * 
*/
void freeHuffmanTree(huffmanTree *tree)
{
    int i;
    for (i = 0; i < tree->size; i++)
        free(tree->array[i]);

    free(tree);
}

huffmanTree *createHuffmanTree(int size)
{
    huffmanTree *tree = (huffmanTree *)malloc(sizeof(huffmanTree));
    tree->array = (huffmanNode **)malloc(sizeof(huffmanNode *) * size);
    for (int i = 0; i < size; i++)
        tree->array[i] = NULL;

    tree->size = size;

    return tree;
}

huffmanTree *buildFromCharactersTable(node table[])
{
    // We can filter the characters table to build the heap nodes
    // to those characters that were counted in the input.
    // Firstly, we calculate 'n', which is the amout of leaf nodes
    // that the Huffman tree will have:
    huffmanTree *tree;
    int n = 0, i, j = 0;

    for (i = 0; i < ALPHABET_LENGTH; i++)
    {
        if (table[i].char_counter != 0)
            n = n + 1;
    }

    tree = createHuffmanTree(n);

    for (i = 0; i < ALPHABET_LENGTH; i++)
    {
        if (table[i].char_counter != 0)
        {
            // Build a new huffman node based on table character data
            // and add that node to the tree
            tree->array[j++] = create_huffman_node(table[i].character, table[i].char_counter);
        }
    }

    return tree;
}

huffmanTree *buildFromPreviousTreeAndFusedNode(huffmanTree *tree, huffmanNode *fused)
{

    int countEnabledNodes = 0;
    for (int i = 0; i < tree->size; i++)
    {
        if (tree->array[i]->enabled)
            countEnabledNodes++;
    }

    //+1 for we are addding in the last position the fused node
    huffmanTree* newTree = createHuffmanTree(countEnabledNodes + 1); 

    int insertedNodes = 0;
    for (int j = 0; j < tree->size; j++)
    {
        huffmanNode* currentNode = tree->array[j];
        if (!currentNode->enabled)
            continue; //skipping, not enabled

        newTree->array[insertedNodes++] = currentNode;
    }

    newTree->array[insertedNodes] = fused;
    //TODO clean previous tree
    return newTree;
}

void build_huffman_tree(node table[])
{
    huffmanTree *tree = buildFromCharactersTable(table);

    //break condition: the huffman tree will
    //be completed whenever our current tree has
    //a single node, whose value is made of the
    //sum of all the other nodes frequency
    while (tree->size > 1)
    {
        huffmanNode *a = extract_min(tree);
        huffmanNode *b = extract_min(tree);

        float resultingFrequency = a->frequency + b->frequency;
        huffmanNode *fused = create_huffman_node('$', resultingFrequency);
        fused->right = a;
        fused->left = b;

        tree = buildFromPreviousTreeAndFusedNode(tree, fused);
    }

    display_huffman_nodes(tree->array, tree->size);
}

int main()
{
    FILE *in = fopen("in.txt", "r");
    node char_table[26];

    if (in == NULL)
    {
        printf("\nError reading file.");
        exit(EXIT_FAILURE);
    }

    init_frequency_table(char_table);
    read_file(in, char_table);
    display_frequency_table(char_table);
    printf("\n\n\n");
    build_huffman_tree(char_table);
    exit(EXIT_SUCCESS);
}
