#include <string.h>
#include <stdlib.h>

#include "stringutils.h"

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