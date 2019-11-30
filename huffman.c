#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET "abcdefghijklmnopqrstuvxyz"
#define ALPHABET_LENGTH 26

/*
	This struct represents each character in the frequency table
*/
typedef struct {
    char character;
    int char_counter;
    float frequency;
} node;

/*
	This struct represents each node in the Huffman tree
*/
typedef struct huffmanNode {
	char character;
	float frequency;
	struct huffmanNode *left;
	struct huffmanNode *right;
} huffmanNode;

/*
	This struct represents the Huffman tree
*/
typedef struct {
	int size;
	huffmanNode *array[25];
} huffmanTree;

void display_frequency_table(node table[]) {
    int i;
    for(i = 0; i < ALPHABET_LENGTH; i++) {
        printf("\n--------");
        printf("\nchar \"%c\" - char_counter = %d - char frequency = %f", table[i].character, table[i].char_counter, table[i].frequency);
    }
}

void display_huffman_nodes(huffmanNode *array[], int size) {
	int i;
	for(i = 0; i < size; i++) {
		printf("\n-------");
		if(array[i]->frequency == -1) printf("\nZERO!");
		printf("\nchar \"%c\" - frequency = %f", array[i]->character, array[i]->frequency);
	}
}

huffmanNode *create_huffman_node(char character, float frequency) {
	huffmanNode *huffNode = malloc(sizeof(huffmanNode));
	
	huffNode->character = character;
	huffNode->frequency = frequency;
	huffNode->left = huffNode->right = NULL;
	
	return huffNode;
}

huffmanNode *extract_min(huffmanNode *array[], int size) {
	huffmanNode *huffMinNode = malloc(sizeof(huffmanNode));
	int i;
	
	// Create a Huffman node with frequency equals to one hundred
	// to start the comparison
	huffMinNode = create_huffman_node('$', 100);
	
	for(i = 0; i < size; i++) {
		if(array[i]->frequency < huffMinNode->frequency) {
			huffMinNode = array[i];
			
			// I's necessary to indicate somehow
			// that the node with the min frequency
			// is removed from the Huffman tree,
			// since it's been added to the min Heap...
			array[i]->frequency = -1; // Não sei se '-1' funciona corretamente
		}
	}
	
	return huffMinNode;
}

//void insert(huffmanNode huffNode, huffmanNode *array[]) {
//	int i;
// do {
//
// } while();
//}

/*
    Initializes a frequency table with all the alphabet characters
    and it's counters to 0
*/
void init_frequency_table(node table[]) {
    int i;
    for(i = 0; i < ALPHABET_LENGTH; i++) {
        table[i].character = ALPHABET[i];
        table[i].char_counter = 0;
    }
}

/*
    Reads the given file and updates the character table with each
    alphabet character occurence and frequency.
*/
void read_file(FILE *file, node table[]) {
    char c;
    int char_counter = 0, i, letter_counter;

    fseek(file, 0, SEEK_SET);

    letter_counter = 0;
    while((c = fgetc(file)) != EOF) {
        if(c != ' ' && c != '.' && c != '\n') {
            c = tolower(c);
            letter_counter = letter_counter + 1;

            for(i = 0; i < ALPHABET_LENGTH; i++) {
                if(c == table[i].character) {
                    table[i].char_counter = table[i].char_counter + 1;
                }
            }
        }
    }

    // Now we can calculate the frequency of each letter in the text
    for(i = 0; i < ALPHABET_LENGTH; i++) {
        float freq = (float) ((float) table[i].char_counter/(float) letter_counter)*100;
        table[i].frequency = freq;
    }
}

void build_huffman_tree(node table[]) {
	huffmanTree *tree = malloc(sizeof(huffmanTree));
	huffmanNode *z;
	// We can filter the characters table to build the heap nodes
	// to those characters that were counted in the input.
	// Firstly, we calculate 'n', which is the amout of leaf nodes
	// that the Huffman tree will have:
	int n = 0, i, j = 0;
	for(i = 0; i < ALPHABET_LENGTH; i++) {
		if(table[i].char_counter != 0) {
			n = n + 1;
		}
	}
	
	for(i = 0; i < ALPHABET_LENGTH; i++) {
		if(table[i].char_counter != 0) {
			// Build a new huffman node based on table character data
			// and add that node to the tree
			tree->array[j] = create_huffman_node(table[i].character, table[i].frequency);
			j = j + 1;
		}
	}
	
	for(i = 0; i < n; i++) {
		z = malloc(sizeof(huffmanNode));
		z = create_huffman_node('$', 0);
		z->left = extract_min(tree->array, n);
		z->right = extract_min(tree->array, n);
		
		// Insert the new node 'z' in the tree...
		
		free(z);
	}
	
	display_huffman_nodes(tree->array, n);
	
}

int main() {
    FILE *in = fopen("in.txt", "r");
    node char_table[25];

    if(in == NULL) {
        printf("\nError reading file.");
        return 1;
    }

    init_frequency_table(char_table);
    read_file(in, char_table);
  	display_frequency_table(char_table);
    printf("\n\n\n");
    build_huffman_tree(char_table);
    return 0;
}
