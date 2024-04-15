#ifndef DIV_TREE_PRINT
#define DIV_TREE_PRINT

typedef struct BinaryTree cache;

static void print_buffer(char *buffer[], int max_Y, int max_X);

char** create_buffer(int rows, int cols);

void delete_buffer(char** buffer, int rows);

void divider_tree_print(int first, int second, BinaryTree * cache);

void node_size(Node * n, int current_x, int current_y, int * max_x, int * max_y, int level);

#endif