#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cache.h"


void build_divider_tree(int number, BinaryTree * bd) {
    binary_tree_insert(number, bd);
    int * interim_dividers = (int *)calloc(sqrt(number), sizeof(int));

    int count = 0;
    int j = 0;
    for (int i = 2; i <= sqrt(number); i++){
        if (number % i == 0)
        {
            binary_tree_insert(i, bd);
            binary_tree_insert(number / i, bd);
            if (i != number/i)
            {
                interim_dividers[j++] = i;
                interim_dividers[j++] = number / i;
                count += 2;
            }
            else
            {
                interim_dividers[j++] = i;
                count += 1;
            }   
        }
    }

    Node * n = binary_tree_find(number, bd);
    n->count_dividers = count;

    if (n->dividers == NULL)
    {
        n->dividers = (Node **)malloc(count * sizeof(Node *));
    }
    
    j = 0;

    for (size_t i = 0; i < count; i++)
    {
        if (interim_dividers[i] != 0)
        {
            if (binary_tree_find(interim_dividers[i], bd) == NULL)
            {
                build_divider_tree(interim_dividers[i], bd);
            }
            n->dividers[j] = binary_tree_find(interim_dividers[i], bd);
            j++;
        }
    }

    free(interim_dividers);
}

void print_node(Node * n){
    printf("%d \n| \n", n->value );
    for (size_t i = 0; i < n->count_dividers; i++) { 
        printf("%d\n| \n", n->dividers[i]->value);
    }
    printf("%d", n->count_dividers);
    printf("\n\n");
}

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