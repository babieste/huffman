#include <stdlib.h>
#include <stdio.h>

#include "stringutils.h"
#include "huffman.h"
#include "heap.h"
#include "map.h"

Map* newMapNode(char character, int position)
{
    Map *map = (Map *) malloc(sizeof(Map));

    map->key = character;
    map->value = position;
    map->nextNode = NULL;

    return map;
}



int isMapped(Map *map, const char character)
{
    if (map == NULL) return -1;
    
    while (map->key != character)
    {
        if (map->nextNode == NULL) return -1;
        
        map = map->nextNode;
    }
    return map->value;
    
}

Map *putToMap(const char character, int position)
{
    Map* newMap = newMapNode(character, position);
    printf("newMap info: %c e %d\n", newMap->key, newMap->value);

    // Map *newMap = (Map *) malloc(sizeof(Map));
    // newMap->key = character;
    // newMap->value = position;
    // newMap->nextNode = NULL;

    // if(current != NULL) current->nextNode = newMap;
    // else head = newMap;

    return newMap;
}