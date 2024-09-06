#include <stdlib.h>
#include <string.h>
#include "../header/stack.h"


#define INITIAL_CAPACITY 10

struct Stack {
    size_t element_size;
    size_t capacity;
    size_t size;
    void *data;
};

// Create a new stack with a specified element size
Stack *stack_create(size_t element_size) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack) {
        stack->element_size = element_size;
        stack->capacity = INITIAL_CAPACITY;
        stack->size = 0;
        stack->data = malloc(element_size * stack->capacity);

        if (!stack->data) {
            free(stack);
            stack = NULL;
        }
    }
    return stack;
}

// Destroy the stack and free its memory
void stack_destroy(Stack *stack) {
    if (stack) {
        free(stack->data);
        free(stack);
    }
}

// Resize the stack to a new capacity
bool stack_resize(Stack *stack, size_t new_capacity) {
    void *new_data = realloc(stack->data, stack->element_size * new_capacity);
    if (new_data) {
        stack->data = new_data;
        stack->capacity = new_capacity;
        return true;
    }
    return false;
}

// Push an element onto the stack
bool stack_push(Stack *stack, const void *element) {
    if (!stack) return false;

    // Resize if needed
    if (stack->size >= stack->capacity) {
        if (!stack_resize(stack, stack->capacity * 2)) {
            return false;
        }
    }

    // Add the element to the stack
    void *dest = (char *)stack->data + stack->element_size * stack->size;
    memcpy(dest, element, stack->element_size);
    stack->size++;
    return true;
}

// Pop an element off the stack (removes the top element)
bool stack_pop(Stack *stack) {
    if (!stack || stack->size == 0) return false;

    stack->size--;

    // Shrink the stack if necessary
    if (stack->size < stack->capacity / 2 && stack->capacity > INITIAL_CAPACITY) {
        stack_resize(stack, stack->capacity / 2);
    }

    return true;
}

// Peek at the top element without removing it
bool stack_peek(const Stack *stack, void *element) {
    if (!stack || stack->size == 0) return false;

    void *src = (char *)stack->data + stack->element_size * (stack->size - 1);
    memcpy(element, src, stack->element_size);

    return true;
}
// Peek at the Nth element without removing it (0-based index)
bool stack_peek_nth(const Stack *stack, size_t index, void *element) {
    if (!stack || index >= stack->size) return false;

    void *src = (char *)stack->data + stack->element_size * index;
    memcpy(element, src, stack->element_size);

    return true;
}


// Check if the stack is empty
bool stack_is_empty(const Stack *stack) {
    return stack ? stack->size == 0 : true;
}

// Get the size of the stack (number of elements)
size_t stack_size(const Stack *stack) {
    return stack ? stack->size : 0;
}
