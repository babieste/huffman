#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heap.h"
#include "huffman.h"
#include "frequence.h"
#include "stringutils.h"

void print_huffman_code (HuffmanCode **code, int size)
{
    printf("-------------- Huffman Code --------------\n");
    for (int i = 0; i < size; i++)
    {
        printf("Character: %c, code = %s\n", code[i]->character, code[i]->code);
    }
    printf("------------------------------------------\n\n");
}

int main()
{

    /*
    First step: receive any string - DONE
    Calculate the frequency of all characters - DONE
    Build, in memory, the huffman tree - DONE
    Print out the frequency of every character and its huffman code - DONE
    Encode informed string
    Decode string previously encoded

    Second step: file management and stuff, later
    */

    /*
    Algorithms using a min heap as a way to extract the nodes with
    the least frequency and build the tree from there:
    https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
   */

    char value[] = "aaaaaaaaaaaaabbbbbccccccccccccccccccccccccddddddddd13214564asdasdasd";
    Frequence *chars_frequence = frequence(value);

    HuffmanCode** result = huffman_code(chars_frequence->letters, chars_frequence->occurrences, chars_frequence->size);

    print_frequence(chars_frequence);
    print_huffman_code(result, chars_frequence->size);
    
    
    char *encodedString = malloc(chars_frequence->size * sizeof(char));
    
    encode(result, value, chars_frequence->size);
    // for (int i = 0; i < strlen(value); i++) 
    // {
        
    //     int j = 0;
    //     while (result[j]->character != value[i])
    //     {
    //         printf("res and val: %c    %c\n",result[j]->character, value[i]);
    //         j++;
    //     }

    //     printf("ACHEI AQUI: %c É %c\n", result[j]->character, value[i]);
    //     printf("PROXIMO I DO FOR\n\n");
    // }


    free_huffman_code(result, chars_frequence->size);
    free_frequence(chars_frequence);
    free(result);

    return 0;
}
