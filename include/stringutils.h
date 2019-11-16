#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include "huffman.h"

char *concat(const char *s1, const char *s2);
char *encode(HuffmanCode **huffman_code, const char *str, int size);


#endif