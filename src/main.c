#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#include "huffman.h"

int main()
{

    /*
    First step: receive any string
    Calculate the frequency of all characters
    Build, in memory, the huffman tree
    Print out the frequency of every character and its huffman code
    Encode informed string
    Decode string previously encoded

    Second step: file management and stuff, later
    */

    /*
    Algorithms using a min heap as a way to extract the nodes with
    the least frequency and build the tree from there:
    https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
   */

    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};

    int size = sizeof(arr) / sizeof(arr[0]);

    huffman_code(arr, freq, size);

    return 0;
}
