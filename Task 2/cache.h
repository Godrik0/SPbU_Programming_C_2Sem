#ifndef CACHE_H_
#define CACHE_H_

typedef struct Node Node;

struct Node{
    int value;
    int count_dividers;
    Node ** dividers;

    Node * left;
    Node * right;
};

typedef struct 
{
    int size;
    Node * root;
} BinaryTree;

typedef struct 
{
    int height;
    int width;
} size;

BinaryTree * binary_tree_init(int key);

void buffer_size(int start, int end, int * size_x, int * size_y, BinaryTree * bd);

void build_divider_tree(int number, BinaryTree * bd);

Node * node_init(int key);

void node_size(Node * n, int current_x, int current_y, int * max_x, int * max_y, int level);

void node_delete(Node * curr);

void binary_tree_free(BinaryTree * bt);

void node_print(Node * curr);

void binary_tree_print(BinaryTree * bt);

Node * binary_tree_find(int key, BinaryTree * bt);

void binary_tree_insert(int key, BinaryTree * bt);

void buildTreeString(Node* node, int level, char* buffer, int* index);

void fill_buffer_node(Node * n, char ** buffer, int current_x, int current_y, int * max_x, int * max_y, int level);

void combining_buffer(char ** first_buffer, char ** second_buffer, int first_x, int first_y, int second_x, int second_y);

void print_number(int number, char ** buffer, int current_x, int current_y);

int number_of_digits(int x);
#endif