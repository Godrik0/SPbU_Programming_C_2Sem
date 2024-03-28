#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cache.h"

BinaryTree * binary_tree_init(int key){
    BinaryTree * bt = (BinaryTree *)malloc(sizeof(BinaryTree));

    if (bt == NULL)
    {
        return NULL;
    }
    
    bt->size = 1;
    bt->root = node_init(key);

    return bt;
}

Node * node_init(int key){
    Node * n =(Node *)malloc(sizeof(Node));
    
    if (n == NULL)
    {
        return NULL;
    }
    
    n->value = key;
    n->count_dividers = 0;
    n->dividers = NULL;
    n->left = NULL;
    n->right = NULL;

    return n;
}

void node_free(Node * curr){
    if(curr != NULL){
        node_free(curr->left);
        node_free(curr->right);
        free(curr->dividers);
        free(curr);
    }
}

void binary_tree_free(BinaryTree * bt){
    node_free(bt->root);
    free(bt);
}

void node_print(Node * curr){
    if (curr != NULL)
    {
        node_print(curr->left);
        printf("%d ", curr->value);
        node_print(curr->right);
    }   
}

void binary_tree_print(BinaryTree * bt){
    node_print(bt->root);
    printf("\n");
}

Node * binary_tree_find(int key, BinaryTree * bt){
    Node * curr = bt->root;

    while(curr != NULL && curr->value != key){
        if (curr->value > key)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }

    return curr;
}

void binary_tree_insert(int key, BinaryTree * bt){
    Node * curr = bt->root;

    while(curr != NULL && curr->value != key){
        if (curr->value > key && curr->left == NULL)
        {
            curr->left = node_init(key);
            bt->size += 1;
            return;
        }
        if(curr->value < key && curr->right == NULL)
        {
            curr->right = node_init(key);
            bt->size += 1;
            return;
        }

        if (curr->value > key)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }
}