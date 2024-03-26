#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cache.h"


void build_divider_tree(int number, BinaryTree * bd) {
    binary_tree_insert(number, bd);
    int * interim_dividers = (int *)calloc(number, sizeof(int));

    int count = 0;
    for (int i = 2; i <= sqrt(number); i++){
        if (number % i == 0)
        {
            binary_tree_insert(i, bd);
            binary_tree_insert(number / i, bd);

            interim_dividers[i] = i;
            interim_dividers[number / i] = number / i;
            count += 2;
        }
    }

    Node * n = binary_tree_find(number, bd);
    n->count_dividers = count;
    n->dividers = (Node **)malloc(count * sizeof(Node));
    int j = 0;
    for (size_t i = 0; i < number; i++)
    {
        if (interim_dividers[i] != 0)
        {
            build_divider_tree(interim_dividers[i], bd);
            n->dividers[j] = binary_tree_find(interim_dividers[i], bd);
            j++;
        }
    }
    
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
    
    BinaryTree * cache = binary_tree_init(32);

    for (size_t i = 20; i <= 32; i++)
    {
        build_divider_tree(i, cache);
    }

    print_node(binary_tree_find(32, cache));

    binary_tree_print(cache);
    
    return 0;
}