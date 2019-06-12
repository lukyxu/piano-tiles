//
// Created by kx3418 on 12/06/19.
//

#ifndef PIANO_TILES_STACK_H
#define PIANO_TILES_STACK_H
#include <stdbool.h>

typedef struct stack_node
{
    int data;
    struct stack_node *next;
}stack_node_t;

typedef stack_node_t *stack;

stack_node_t *new_node(int data);

bool stack_empty(stack root);
void push(stack *root, int data);

int pop(stack *root);

int peek(stack root);
#endif //PIANO_TILES_STACK_H
