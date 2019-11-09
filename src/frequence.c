#include <stdlib.h>
#include <stdio.h>

#include "frequence.h"

void print_frequence(Frequence *frequence)
{
    for (int i = 0; i < frequence->size; i++)
    {
        printf("%c - %d\n", frequence->letters[i], frequence->occurrences[i]);
    }
}

/**
 * Utility function to free a frequence struct and 
 * all of its pointers
*/
void free_frequence(Frequence *frequence)
{
    free(frequence->letters);
    free(frequence->occurrences);
    free(frequence);
}

/**
 * Init the frequence struct considering the ascii table
 * So all values will be added, from 0  to ASCII_CHARS
 * and their occurrences will be 0
 * 
 * Not responsible for freeing the Frequence struct 
*/
Frequence *init_ascii_chars()
{
    Frequence *frequence = (Frequence *)malloc(sizeof(Frequence));

    frequence->letters = (char *)malloc(sizeof(char) * ASCII_CHARS);
    frequence->occurrences = (int *)malloc(sizeof(int) * ASCII_CHARS);
    frequence->size = ASCII_CHARS;

    for (int i = 0; i <= ASCII_CHARS; i++)
    {
        frequence->occurrences[i] = 0;
        frequence->letters[i] = i;
    }

    return frequence;
}

/**
 * Utility function to count the number of chars 
 * that had at least one occurrence on the 
 * Frequence passed as parameter
 * 
*/
int num_used_chars(Frequence *frequence)
{    
    int used_chars = 0;

    for (int i = 0; i < frequence->size; i++)
    {
        if (frequence->occurrences[i] > 0) 
            used_chars++;
    }

    return used_chars;
}

/**
 * Receive a Frequence struct including all the ascii characters
 * Return a new Frequence including only the ones that had at least one ocurrence
 * 
 * Responsible for frequence passed as parameter, as it is creating a new struct
*/
Frequence *remove_unused_chars(Frequence *frequence)
{
    int used_chars = num_used_chars(frequence);

    //initing frequence
    Frequence *temp_frequence = (Frequence *)malloc(sizeof(Frequence));

    temp_frequence->letters = (char *)malloc(sizeof(char) * used_chars);
    temp_frequence->occurrences = (int *)malloc(sizeof(int) * used_chars);
    temp_frequence->size = used_chars;

    int inserted_chars = 0;
    for (int i = 0; i < frequence->size; i++)
    {
        if (frequence->occurrences[i] > 0)
        {
            temp_frequence->letters[inserted_chars] = frequence->letters[i];
            temp_frequence->occurrences[inserted_chars] = frequence->occurrences[i];

            inserted_chars++;
        }
    }

    free_frequence(frequence);
    return temp_frequence;
}

/**
 * Init the frequence struct; iterates over the string passed as 
 * parameter and count the occurrences of each char. 
 * 
 * Not responsible for freeing the Frequence struct 
*/
Frequence *frequence(char value[])
{
    Frequence *frequence = init_ascii_chars();

    for (unsigned int i = 0; i < strlen(value); i++)
    {
        char current_char = value[i];
        frequence->occurrences[current_char]++;
    }

    return remove_unused_chars(frequence);
}