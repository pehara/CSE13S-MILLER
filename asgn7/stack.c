//stack ADT
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "stack.h"


struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

//constructor for stack
Stack *stack_create(uint32_t capacity) {
    struct Stack *s  = (struct Stack *)malloc(sizeof(struct Stack));

    s->top = 0;
    s->capacity = capacity;
    s->items = (struct Node **)malloc(capacity * sizeof(struct Node *));

    return s;
}

//destructor for stack
void stack_delete(Stack **s) {
    free(*s);
    *s = NULL;
}

//Returns true if the stack is empty and false otherwise
bool stack_empty(Stack *s) {
    if ((stack_size(s)) == 0) {
        return true;
    }
    else {
        return false;
    }
}

//Returns true if the stack is full and false otherwise
bool stack_full(Stack *s) {
    if (stack_size(s) == s->capacity) {
        return true;
    }
    else {
        return false;
    }
}

//returns the number of nodes in the stack
uint32_t stack_size(Stack *s) {
    return (s->top);
}

//Pushes a node onto the stack
bool stack_push(Stack *s, Node *n) {
    if (stack_full(s)) {
        return false;
    }
	
    s->items[s->top] = n; // Push the new item and increment top
    s->top++;

    return true;
}

//Pops a node off the stack
bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s)) {
        return false;
    }

	*n = s->items[s->top];
    s->top--;

    return true;
}

//debug function for stack
void stack_print(Stack *s) {
    printf("\nStack: top %u, capacity %u", s->top, s->capacity);
}



