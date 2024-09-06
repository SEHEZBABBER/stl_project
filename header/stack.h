#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack Stack;

// Create a new stack with a specified element size
Stack *stack_create(size_t element_size);

// Destroy the stack and free its memory
void stack_destroy(Stack *stack);

// Push an element onto the stack
bool stack_push(Stack *stack, const void *element);

// Pop an element off the stack
bool stack_pop(Stack *stack);

// Peek at the top element without removing it
bool stack_peek(const Stack *stack, void *element);

// Peek at the Nth element without removing it (0-based index)
bool stack_peek_nth(const Stack *stack, size_t index, void *element);

// Check if the stack is empty
bool stack_is_empty(const Stack *stack);

// Get the size of the stack (number of elements)
size_t stack_size(const Stack *stack);

#endif // STACK_H
