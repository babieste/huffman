#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "stringutils.h"
#include "huffman.h"
#include "heap.h"
#include "map.h"

char *concat(const char *s1, const char *s2)
{
    char *result = (char *)malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator

    if (result == NULL)
    {
        // strerror("Error while concatening strings");
        exit(EXIT_FAILURE);
    }

    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

// TODO: map sendo sobrescrito
char *encode(HuffmanCode **huffman_code, const char *str, int size) 
{
    Map *map = newMapNode(NULL, NULL);

    char *encodedString = malloc(sizeof(char));

    for (int i = 0; i < strlen(str); i++) 
    {
        char letterToBeEncoded = str[i];
        // verifica se a letra ja esta mapeada
        printf("verificando se letra '%c' ja se encontra mapeado\n", letterToBeEncoded);

        int index = isMapped(map, letterToBeEncoded);
        if (index != -1)
        {
            printf("letra '%c' ja esta mapeada para o index %d\n", letterToBeEncoded, index);
            encodedString = concat(encodedString, huffman_code[index]->code);   
            printf("string codificada: %s\n", encodedString);
        } else {

            
            int j = 0;
            for (; huffman_code[j]->character != letterToBeEncoded; j++);
            
            
            printf("\n\nMapeando char '%c' para a posicao %d da arvore\n\n", huffman_code[j]->character, j);
            map = putToMap(str[i], j);
        }

    }
    
}