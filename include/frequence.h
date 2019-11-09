#ifndef FREQUENCE_H
#define FREQUENCE_H

#include <string.h>

#define ASCII_CHARS 127

/*
 * letters[x] had occurrence[x] ocurrences
*/
typedef struct
{
    char *letters;
    int *occurrences;
    int size;
} Frequence;

void print_frequence (Frequence * frequence);
void free_frequence (Frequence *frequence);
Frequence *init_ascii_chars ();
Frequence *remove_unused_chars (Frequence *frequence);
Frequence *frequence(char value[]);

#endif