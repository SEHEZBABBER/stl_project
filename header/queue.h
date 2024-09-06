#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Queue Queue;  // Forward declaration

// Queue operations
Queue *queue_create(size_t element_size);
void queue_destroy(Queue *queue);
bool queue_resize(Queue *queue, size_t new_capacity);
bool queue_enqueue(Queue *queue, const void *element);
bool queue_dequeue(Queue *queue);
bool queue_peek(const Queue *queue, void *element);
bool queue_is_empty(const Queue *queue);
bool queue_peek_nth(const Queue *queue, size_t index, void *element);
size_t queue_size(const Queue *queue);

#endif // QUEUE_H
