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

BinaryTree * binary_tree_init(int key);

Node * node_init(int key);

void node_delete(Node * curr);

void binary_tree_free(BinaryTree * bt);

void node_print(Node * curr);

void binary_tree_print(BinaryTree * bt);

Node * binary_tree_find(int key, BinaryTree * bt);

void binary_tree_insert(int key, BinaryTree * bt);

#endif