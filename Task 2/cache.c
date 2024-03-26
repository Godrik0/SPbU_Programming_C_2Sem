#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "header.h"

BinaryTree * binary_tree_init(int key){
    BinaryTree * bt = (BinaryTree *)malloc(sizeof(BinaryTree));

    bt->size = 1;
    bt->root = (Node *)malloc(sizeof(Node));

    bt->root->value = key;
    bt->root->left = NULL;
    bt->root->right = NULL;
}

void node_delete(Node * curr){
    if(curr != NULL){
        node_delete(curr->left);
        node_delete(curr->right);
        free(curr);
    }
}

void binary_tree_free(BinaryTree * bt){
    node_delete(bt->root);
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
            curr->left = (Node *)malloc(sizeof(Node));
            bt->size += 1;
            return;
        }
        if(curr->value < key && curr->right == NULL)
        {
            curr->right = (Node *)malloc(sizeof(Node));
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

int main(){
    return 0;
}