#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cache.h"

int main(){

    int start, end, input;
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

    printf("Output of all divisors: [1]\nOutput of the divisors of a number: [2]\n");
    scanf("%d", &input);
    switch (input)
    {
    case 1:
        binary_tree_print(cache);
        break;

    case 2:
        printf("Input number: ");
        scanf("%d", &input);

        Node * inp = binary_tree_find(input, cache);

        if (inp != NULL)
        {
            print_node(inp);
        }
        else
        {
            printf("This number is missing");
        }

        break;

    default:
        printf("Incorrect input.");
        break;
    }
    
    binary_tree_free(cache);
    
    return 0;
}