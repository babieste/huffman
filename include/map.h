#ifndef MAP_H
#define MAP_H

typedef struct Map
{
    char key;
    int value;
    struct Map *nextNode;
} Map;

Map *newMapNode(char character, int position);
int isMapped(Map *map, const char character);
Map *putToMap( const char character, int position);

#endif