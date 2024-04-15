#ifndef CACHE_H_
#define CACHE_H_

#define MAX(a,b) ({int _a = (a), _b = (b); _a > _b ? _a : _b; })
#define MIN(a,b) ({int _a = (a), _b = (b); _a < _b ? _a : _b; })

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

void build_divider_tree(int number, BinaryTree * bd);

Node * node_init(int key);

void node_delete(Node * curr);

void binary_tree_free(BinaryTree * bt);

void binary_tree_print(BinaryTree * bt);

Node * binary_tree_find(int key, BinaryTree * bt);

void binary_tree_insert(int key, BinaryTree * bt);
#endif