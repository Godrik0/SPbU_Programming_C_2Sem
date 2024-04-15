#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cache.h"

static void print_buffer(char *buffer[], int max_Y, int max_X) {
    char name_file[] = "output.txt";
    FILE* file = fopen(name_file, "w");
    for (int i = 0; i < max_Y; i++) {
        for(int j = 0; j < max_X; j++) {
            fprintf(file, "%c", buffer[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

char** create_buffer(int rows, int cols) {
    char **buffer = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        buffer[i] = (char *)malloc(cols * sizeof(char));
        for (int j = 0; j < cols; j++) {
            buffer[i][j] = ' ';
        }
    }
    return buffer;
}

void delete_buffer(char** buffer, int rows){
    for (int i = 0; i < rows; i++)
    {
        free(buffer[i]);
    }
    free(buffer);
}

char ** combining_buffers(char ** first_buffer, char ** second_buffer, int first_x, int first_y, int second_x, int second_y, int minimization){
    char **output = create_buffer(MAX(first_y, second_y), MAX(minimization + second_x, first_x));
    int x = 0;
    int y = 0;
    for (x = 0; x < first_x; x++)
    {
        for (y = 0; y < first_y; y++)
        {
            output[y][x] = first_buffer[y][x];
        }
        
    }

    x = minimization;
    y = 0;

    for (int i = 0; i < second_x; i++)
    {
        for (int j = 0; j < second_y; j++)
        {
            output[y+j][x+i] = second_buffer[j][i];
        }
        
    }

    for (int i = 0; i <= minimization; i++)
    {
        if (output[0][i] == ' ')
        {
            output[0][i] = '-';
        }
        
    }
    
    return output;
}

void divider_tree_print(int first, int second, BinaryTree * cache){
    int first_max_x = number_of_digits(first);
    int first_max_y = 1;
    int second_max_x = number_of_digits(first+1);
    int second_max_y = 1;

    int first_x = 1;
    int first_y = 1;
    int second_x = 1;
    int second_y = 1;

    int minimization = 0; 

    char ** temp;

    node_size(binary_tree_find(first, cache), 0, 0, &first_max_x, &first_max_y, 0);
    first_max_x += number_of_digits(first);
    first_max_y++;
    char **first_buffer = create_buffer(first_max_y, first_max_x);
    fill_buffer_node(binary_tree_find(first, cache), first_buffer, 0, 0, &first_x, &first_y, 0);

    for (int i = first + 1; i <= second; i++)
    {
        second_max_x = number_of_digits(i);
        second_max_y = 1;
        second_x = 1;
        second_y = 1;

        node_size(binary_tree_find(i, cache), 0, 0, &second_max_x, &second_max_y, 0);
        second_max_x += number_of_digits(i);
        second_max_y++;

        char **second_buffer = create_buffer(second_max_y, second_max_x);
        fill_buffer_node(binary_tree_find(i, cache), second_buffer, 0, 0, &second_x, &second_y, 0);
        
        minimization = calculation_minimization(first_buffer, first_max_x, first_max_y, second_max_x, second_max_y);

        temp = combining_buffers(first_buffer, second_buffer, first_max_x, first_max_y, second_max_x, second_max_y, minimization);
        print_buffer(temp, MAX(first_max_y, second_max_y), MAX(minimization + second_max_x, first_max_x));

        delete_buffer(second_buffer, second_max_y);
        delete_buffer(first_buffer, first_max_y);
        first_buffer = temp;

        first_max_x = MAX(minimization + second_max_x, first_max_x);
        first_max_y = MAX(first_max_y, second_max_y);
    }
    delete_buffer(temp, MAX(first_max_y, second_max_y));
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
            update_max_size(current_x, current_y, max_x, max_y);
        }      
    }
    
    update_max_size(current_x, current_y, max_x, max_y);

}

int calculation_minimization(char ** first_buffer, int first_x, int first_y, int second_x, int second_y){
    int i = first_x - 1;
    for (i; i >= 0; i--)
    {
        for (int j = 0; j < MIN(first_y, second_y); j++)
        {
            if (first_buffer[j][i] != ' ')
            {
                return i + 2;
            }
            
        }        
    }
    return i;
}
