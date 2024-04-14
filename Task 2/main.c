#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cache.h"

static void print_buffer(char *buffer[], int max_Y, int max_X) {
    char* name_file = "suspension.txt";
    FILE* file = fopen(name_file, "w");
    for (int i = 1; i < max_Y; i++) {
        for(int j = 1; j < max_X; j++) {
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

void print_min(int first, int second, BinaryTree * cache){
    int first_max_x = number_of_digits(first) + 1;
    int first_max_y = 0;
    int second_max_x = number_of_digits(second) + 1;
    int second_max_y = 0;

    int first_x = 0;
    int first_y = 0;
    int second_x = 0;
    int second_y = 0;


    node_size(binary_tree_find(first, cache), 0, 0, &first_max_x, &first_max_y, 0);
    char **first_buffer = create_buffer(first_max_y + 2, first_max_x);
    fill_buffer_node(binary_tree_find(first, cache), first_buffer, 1, 1, &first_x, &first_y, 0);

    node_size(binary_tree_find(second, cache), 0, 0, &second_max_x, &second_max_y, 0);
    char **second_buffer = create_buffer(second_max_y + 2, second_max_x);
    fill_buffer_node(binary_tree_find(second, cache), second_buffer, 1, 1, &second_x, &second_y, 0);

    combining_buffer(first_buffer, second_buffer, first_max_x, first_max_y + 2, second_max_x, second_max_y + 2);
    print_buffer(first_buffer, first_max_y + 2, first_max_x);

}

int main(){

    int start, end, input;
    printf("Enter start: ");
    scanf("%d", &start);
    printf("Enter end: ");
    scanf("%d", &end);
    
    // if (start < 0 || end < 0 || end < start)
    // {
    //     printf("Incorrect input. Restart the program.\n");
    //     return 0;
    // }
    
    BinaryTree * cache = binary_tree_init(end);

    for (size_t i = start; i <= end; i++)
    {
        build_divider_tree(i, cache);
    }

    //char buffer[100];
    print_min(1000, 1001, cache);

    // Построение строки для дерева
    // buildTreeString(binary_tree_find(10, cache), 0, buffer, &index);
    // buffer[index] = '\0';

    
    // Вывод строки с деревом
    //printf("%d\t %d", s.height, s.width);

    // printf("Output of all divisors: [1]\nOutput of the divisors of a number: [2]\n");
    // scanf("%d", &input);
    // switch (input)
    // {
    // case 1:
    //     binary_tree_print(cache);
    //     break;

    // case 2:
    //     printf("Input number: ");
    //     scanf("%d", &input);

    //     Node * inp = binary_tree_find(input, cache);

    //     if (inp != NULL)
    //     {
    //         print_node(inp);
    //     }
    //     else
    //     {
    //         printf("This number is missing");
    //     }

    //     break;

    // default:
    //     printf("Incorrect input.");
    //     break;
    // }
    
    binary_tree_free(cache);
    
    return 0;
}