#ifndef DIV_TREE_PRINT
#define DIV_TREE_PRINT

#include "binary_tree.h"

typedef struct 
{
    char ** data;
    int x;
    int y;
} Buffer;

void divider_tree_print(int start, int end, BinaryTree * cache);

#endif
