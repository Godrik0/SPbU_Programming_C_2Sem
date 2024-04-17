#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cache.h"
#include "divider_tree_print.h"

int main(){

    int start, end;
    printf("Enter start: ");
    scanf("%d", &start);
    printf("Enter end: ");
    scanf("%d", &end);
    
    if (start < 0 || end < 0 || end < start)
    {
        printf("Incorrect input. Restart the program.\n");
        return 0;
    }
    
    BinaryTree * cache = binary_tree_init(end);

    for (size_t i = start; i <= end; i++)
    {
        build_divider_tree(i, cache);
    }

    
    divider_tree_print(start, end, cache);
    
    binary_tree_free(cache);
    
    return 0;
}