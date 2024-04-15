#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cache.h"

int compare_int(const void *a, const void *b) {
    int a1 = *(const int *)a;
    int b1 = *(const int *)b;
    return a1 - b1;
}

void build_divider_tree(int number, BinaryTree * bd) {
    binary_tree_insert(number, bd);
    int NN = sqrt(number) * 2;
    int * interim_dividers = (int *)calloc(NN, sizeof(int));

    int count = 0;
    int j = 0;
    for (int i = 2; i <= sqrt(number); i++){
        if (number % i == 0)
        {
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

    qsort(interim_dividers, NN, sizeof(*interim_dividers),compare_int);

    Node * n = binary_tree_find(number, bd);
    n->count_dividers = count;

    if (n->dividers == NULL)
    {
        n->dividers = (Node **)malloc(count * sizeof(Node *));
    }
    
    j = 0;

    for (size_t i = 0; i < NN; i++)
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
