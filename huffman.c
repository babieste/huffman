#include <stdio.h>
#include <ctype.h>

#define ALPHABET "abcdefghijklmnopqrstuvxyz"
#define ALPHABET_LENGTH 26

typedef struct {
    char character;
    int char_counter;
    float frequency;
} node;

void display_frequency_table(node table[]) {
    int i;
    for(i = 0; i < ALPHABET_LENGTH; i++) {
        printf("\n--------");
        printf("\nchar \"%c\" - char_counter = %d - char frequency = %f", table[i].character, table[i].char_counter, table[i].frequency);
    }
}

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
    return 0;
}