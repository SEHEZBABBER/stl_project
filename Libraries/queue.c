#include <stdlib.h>
#include <string.h>
#include "../header/queue.h"

#define INITIAL_CAPACITY 10

struct Queue {
    size_t element_size;
    size_t capacity;
    size_t size;
    size_t front;
    size_t back;
    void *data;
};

// Create a new queue with a specified element size
Queue *queue_create(size_t element_size) {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (queue) {
        queue->element_size = element_size;
        queue->capacity = INITIAL_CAPACITY;
        queue->size = 0;
        queue->front = 0;
        queue->back = 0;
        queue->data = malloc(element_size * queue->capacity);

        if (!queue->data) {
            free(queue);
            queue = NULL;
        }
    }
    return queue;
}

// Destroy the queue and free its memory
void queue_destroy(Queue *queue) {
    if (queue) {
        free(queue->data);
        free(queue);
    }
}

// Resize the queue to a new capacity
bool queue_resize(Queue *queue, size_t new_capacity) {
    void *new_data = malloc(queue->element_size * new_capacity);
    if (!new_data) return false;

    // Copy elements to new data array
    for (size_t i = 0; i < queue->size; i++) {
        void *src = (char *)queue->data + queue->element_size * ((queue->front + i) % queue->capacity);
        void *dest = (char *)new_data + queue->element_size * i;
        memcpy(dest, src, queue->element_size);
    }

    free(queue->data);
    queue->data = new_data;
    queue->capacity = new_capacity;
    queue->front = 0;
    queue->back = queue->size;
    return true;
}

// Enqueue an element to the back of the queue
bool queue_enqueue(Queue *queue, const void *element) {
    if (!queue) return false;

    // Resize if needed
    if (queue->size >= queue->capacity) {
        if (!queue_resize(queue, queue->capacity * 2)) {
            return false;
        }
    }

    // Add element to the back of the queue
    void *dest = (char *)queue->data + queue->element_size * queue->back;
    memcpy(dest, element, queue->element_size);
    queue->back = (queue->back + 1) % queue->capacity;
    queue->size++;
    return true;
}

// Dequeue an element from the front of the queue
bool queue_dequeue(Queue *queue) {
    if (!queue || queue->size == 0) return false;

    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    // Shrink the queue if necessary
    if (queue->size < queue->capacity / 2 && queue->capacity > INITIAL_CAPACITY) {
        queue_resize(queue, queue->capacity / 2);
    }

    return true;
}

// Peek at the front element without removing it
bool queue_peek(const Queue *queue, void *element) {
    if (!queue || queue->size == 0) return false;

    void *src = (char *)queue->data + queue->element_size * queue->front;
    memcpy(element, src, queue->element_size);

    return true;
}
bool queue_peek_nth(const Queue *queue, size_t index, void *element) {
    if (!queue || index >= queue->size) return false;

    size_t actual_index = (queue->front + index) % queue->capacity;
    void *src = (char *)queue->data + queue->element_size * actual_index;
    memcpy(element, src, queue->element_size);

    return true;
}
// Check if the queue is empty
bool queue_is_empty(const Queue *queue) {
    return queue ? queue->size == 0 : true;
}

// Get the size of the queue (number of elements)
size_t queue_size(const Queue *queue) {
    return queue ? queue->size : 0;
}
