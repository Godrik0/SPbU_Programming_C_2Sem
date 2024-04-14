#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cache.h"

#define MAX(a,b) ({int _a = (a), _b = (b); _a > _b ? _a : _b; })
#define MIN(a,b) ({int _a = (a), _b = (b); _a < _b ? _a : _b; })

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

void print_node(Node * n){
    printf("%d \n| \n", n->value );
    for (size_t i = 0; i < n->count_dividers; i++) { 
        printf("%d\n| \n", n->dividers[i]->value);
    }
    printf("%d", n->count_dividers);
    printf("\n\n");
}

int number_of_digits(int x){
    return floor(log10(x)) + 1;
}

void update_max_size(int current_x, int current_y, int * max_x, int * max_y){
    *max_x = MAX(current_x, *max_x);
    *max_y = MAX(current_y, *max_y);    
}

void node_size(Node * n, int current_x, int current_y, int * max_x, int * max_y, int level){
    if (n->count_dividers == 0)
    {
        update_max_size(current_x + number_of_digits(n->value), current_y,
        max_x, max_y);
        return;
    }
    
    if (level % 2 == 0)
    {
        for (int i = 0; i < n->count_dividers; i++)
        {
            int temp_max_y = 1;
            current_y += 1;
            node_size(n->dividers[i], current_x, ++current_y,
            max_x, &temp_max_y, level + 1);

            int temp_min_y = temp_max_y - current_y;
            if (n->count_dividers - 1 == i)
            {
                for (int i = 0; i < temp_min_y; i++)
                {
                    current_y++;
                }
                update_max_size(current_x, current_y, max_x, max_y);
                continue;
            }
            
            for (int i = 0; i < temp_min_y; i++)
            {
                current_y++;
            }   
        }   
    }
    else
    {
        current_x += number_of_digits(n->value) - 1;
        for (int i = 0; i < n->count_dividers; i++)
        {
            current_x += 1;
            int temp_max_x = 1;
            node_size(n->dividers[i], ++current_x, current_y, &temp_max_x, max_y, level + 1);
            current_x += number_of_digits(n->dividers[i]->value) - 1;

            int temp_min_x = temp_max_x - current_x;
            if (n->count_dividers - 1 == i)
            {
                for (int i = 0; i < temp_min_x; i++)
                {
                    current_x++;
                }
                update_max_size(current_x, current_y, max_x, max_y);
                continue;
            }
            
            for (int i = 0; i < temp_min_x - 1; i++)
            {
                current_x++;
            }
        }   
    }
    update_max_size(current_x, current_y, max_x, max_y);
}

void buffer_size(int start, int end, int * size_x, int * size_y, BinaryTree * bd){
    for (size_t i = start; i <= end; i++)
    {
        int temp_x = 0;
        int temp_y = 0;

        node_size(binary_tree_find(i, bd), 0, 0, &temp_x, &temp_y, 0);

        *size_x = *size_x + temp_x + 1;
        *size_y = MAX(*size_y, temp_y);
    }
}

void print_number(int number, char ** buffer, int current_x, int current_y){
    current_x += number_of_digits(number) - 1;
    int size = number_of_digits(number);
    for (int i = 0; i < size; i++)
    {
        buffer[current_y][current_x--] = '0' + number%10;
        number /= 10;
    }
}


void fill_buffer_node(Node * n, char ** buffer, int current_x, int current_y, int * max_x, int * max_y, int level){
    print_number(n->value, buffer, current_x, current_y);
    if (n->count_dividers == 0)
    {
        update_max_size(current_x, current_y, max_x, max_y);
        return;
    }
    if (level % 2 ==0)
    {
        for (int i = 0; i < n->count_dividers; i++)
        {
            current_y++;
            buffer[current_y++][current_x] = '|';
            int temp_max_y = 1;
            fill_buffer_node(n->dividers[i], buffer, current_x, current_y, max_x, &temp_max_y, level + 1);   

            int temp_min_y = temp_max_y - current_y;
            if (n->count_dividers - 1 == i)
            {
                for (int i = 0; i < temp_min_y; i++)
                {
                    current_y += 1;
                }
                update_max_size(current_x, current_y, max_x, max_y);
                continue;
            }
            
            for (int i = 0; i < temp_min_y; i++)
            {
                buffer[++current_y][current_x] = '|';
            }   

        }
        
    }
    
    else{
        //print_number(n->value, buffer, current_x, current_y);
        current_x += number_of_digits(n->value) - 1;
        for (int i = 0; i < n->count_dividers; i++)
        {
            buffer[current_y][++current_x] = '-';
            int temp_max_x = 1;
            fill_buffer_node(n->dividers[i], buffer, ++current_x, current_y, &temp_max_x, max_y, level + 1);
            current_x += number_of_digits(n->dividers[i]->value) - 1;

            int temp_min_x = temp_max_x - current_x;
            if (n->count_dividers - 1 == i)
            {
                for (int i = 0; i < temp_min_x; i++)
                {
                    current_x++;
                }
                update_max_size(current_x, current_y, max_x, max_y);
                continue;
            }
            
            for (int i = 0; i < temp_min_x; i++)
            {
                buffer[current_y][++current_x] = '-';
            }
        }      
    }
    
    update_max_size(current_x, current_y, max_x, max_y);

}

void combining_buffer(char ** first_buffer, char ** second_buffer, int first_x, int first_y, int second_x, int second_y){
    int i = 0;
    int j = 0;
    for (i = MIN(first_x, second_x); i >= 0; i--)
    {
        int flag = 0;
        for (j = 0; j < MIN(first_y, second_y); j++)
        {
            if (first_buffer[j][i] != ' ' || second_buffer[j][i] != ' ')
            {
                printf("x: %d\n", first_x - i);
                return;
            }
            
        }
    }
    
    

}
