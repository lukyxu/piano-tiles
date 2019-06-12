//
// Created by kx3418 on 12/06/19.
//
#include <stdlib.h>
#include <limits.h>
#include "stack.h"
stack_node_t *new_node(int data){
    stack_node_t *node = malloc(sizeof(stack_node_t));
    node->next = NULL;
    node->data = data;
    return node;
}

bool stack_empty(stack root){
    return !root;
}

void push(stack *root, int data){
    stack_node_t *next_node = new_node(data);
    next_node->next = *root;
    *root = next_node;
}

int pop(stack *root){
    if (stack_empty(*root)){
        return INT_MIN;
    }
    stack_node_t *popped_node = *root;
    *root = (*root)->next;
    int output = popped_node->data;
    free(popped_node);
    return output;
}

int peek(stack root) {
    if (stack_empty(root)) {
        return INT_MIN;
    }
    return root->data;
}