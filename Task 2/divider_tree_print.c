#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "binary_tree.h"
#include "divider_tree_print.h"

static int max(int first, int second){
    if (first >= second)
        return first;  
    else 
        return second; 
}

static int min(int first, int second){
    if (first < second)
        return first;  
    else 
        return second; 
}

void print_buffer(Buffer * buffer) {
    char name_file[] = "output.txt";
    FILE* file = fopen(name_file, "w");
    for (int i = 0; i < buffer->y; i++) {
        for(int j = 0; j < buffer->x; j++) {
            fprintf(file, "%c", buffer->data[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

Buffer * create_buffer(int cols, int rows) {
    Buffer *buffer = (Buffer*)malloc(sizeof(Buffer));
    buffer->data = (char**)malloc(cols * sizeof(char*));
    buffer->x = rows;
    buffer->y = cols;
    for (int i = 0; i < cols; i++) {
        buffer->data[i] = (char *)malloc(rows * sizeof(char));
        for (int j = 0; j < rows; j++) {
            buffer->data[i][j] = ' ';
        }
    }
    return buffer;
}

void delete_buffer(Buffer * buffer){
    for (int i = 0; i < buffer->y; i++)
    {
        free(buffer->data[i]);
    }
    free(buffer->data);
    free(buffer);
}

Buffer * combining_buffers(Buffer * first_buffer, Buffer * second_buffer,
                          int minimization){
    Buffer * output = create_buffer(max(first_buffer->y, second_buffer->y),
                                    max(minimization + second_buffer->x, 
                                        first_buffer->x));
    int x = 0;
    int y = 0;
    for (x = 0; x < first_buffer->x; x++)
    {
        for (y = 0; y < first_buffer->y; y++)
        {
            output->data[y][x] = first_buffer->data[y][x];
        }
        
    }

    x = minimization;
    y = 0;

    for (int i = 0; i < second_buffer->x; i++)
    {
        for (int j = 0; j < second_buffer->y; j++)
        {
            output->data[y+j][x+i] = second_buffer->data[j][i];
        }
        
    }

    for (int i = 0; i <= minimization; i++)
    {
        if (output->data[0][i] == ' ')
        {
            output->data[0][i] = '-';
        }
        
    }
    
    return output;
}

int number_of_digits(int x){
    return floor(log10(x)) + 1;
}

int calculation_minimization(Buffer * first_buffer, Buffer * second_buffer){
    int i = 0;
    for (i = first_buffer->x - 1; i >= 0; i--)
    {
        for (int j = 0; j < min(first_buffer->y, second_buffer->y); j++)
        {
            if (first_buffer->data[j][i] != ' ')
            {
                return i + 2;
            }
            
        }        
    }
    return i;
}

void update_max_size(int current_x, int current_y, int * max_x, int * max_y){
    *max_x = max(current_x, *max_x);
    *max_y = max(current_y, *max_y);    
}

void node_size(Node * n, int current_x, int current_y, 
               int * max_x, int * max_y, int level){
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
            node_size(n->dividers[i], ++current_x, current_y, &temp_max_x, 
                      max_y, level + 1);
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

static void fill_buffer_node(Node * n, char ** buffer, int current_x, 
                        int current_y, int * max_x, int * max_y, int level){
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
            fill_buffer_node(n->dividers[i], buffer, current_x, current_y,
                             max_x, &temp_max_y, level + 1);   

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
            fill_buffer_node(n->dividers[i], buffer, ++current_x, 
                             current_y, &temp_max_x, max_y, level + 1);
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

void divider_tree_print(int start, int end, BinaryTree * cache){
    int first_max_x = number_of_digits(start);
    int first_max_y = 1;
    int second_max_x = number_of_digits(start+1);
    int second_max_y = 1;

    int first_x = 1;
    int first_y = 1;
    int second_x = 1;
    int second_y = 1;

    int minimization = 0; 

    Buffer * temp = 0;

    node_size(binary_tree_find(start, cache), 0, 0, 
              &first_max_x, &first_max_y, 0);
    first_max_x += number_of_digits(start);
    first_max_y++;

    Buffer * first_buffer = create_buffer(first_max_y, first_max_x);
    fill_buffer_node(binary_tree_find(start, cache), first_buffer->data, 0, 0, 
                     &first_x, &first_y, 0);

    for (int i = start + 1; i <= end; i++)
    {
        second_max_x = number_of_digits(i);
        second_max_y = 1;
        second_x = 1;
        second_y = 1;
        node_size(binary_tree_find(i, cache), 0, 0, 
                  &second_max_x, &second_max_y, 0);
        second_max_x += number_of_digits(i);
        second_max_y++;

        Buffer * second_buffer = create_buffer(second_max_y, second_max_x);
        fill_buffer_node(binary_tree_find(i, cache), second_buffer->data, 0, 0, 
                         &second_x, &second_y, 0);
        
        minimization = calculation_minimization(first_buffer, second_buffer);

        temp = combining_buffers(first_buffer, second_buffer, minimization);

        delete_buffer(second_buffer);
        delete_buffer(first_buffer);
        first_buffer = temp;

        first_max_x = max(minimization + second_max_x, first_max_x);
        first_max_y = max(first_max_y, second_max_y);
    }
    print_buffer(temp);
    delete_buffer(temp);
}
