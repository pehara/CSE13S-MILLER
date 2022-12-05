//my implementation of the node ADT
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "node.h"


//constructor for node
Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->left = NULL;
        n->right = NULL;
        n->symbol = symbol;
        n->frequency = frequency;
    }
    return n;
}

//destructor for node
void node_delete(Node **n) {
    free(*n);
    *n = NULL;
}

//Joins a left child node and right child node, returning a pointer to a created parent node
Node *node_join(Node *left, Node *right) {
    Node *newnode = node_create('$', (left->frequency + right->frequency));
    
    newnode->left = left;
    newnode->right = right;

    return newnode;
}

//debug function 
void node_print(Node *n) {
    printf("debug statement for node, ");
      
    printf("left: %s right: %s symbol: %d frequency: %lu \n", (n->left == NULL ? "NULL" : "-"), (n->right == NULL ? "NULL" : "-"), n->symbol, n->frequency);
}
