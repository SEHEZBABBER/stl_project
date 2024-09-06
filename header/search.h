#ifndef SEARCH_H
#define SEARCH_H

#include <stdbool.h>

// Function pointer for iterating over elements
typedef bool (*IteratorFunc)(void *data_structure, size_t index, void *element);

// Generic search function that works with any data structure
bool search(void *data_structure, IteratorFunc iterator, size_t size, const void *target, size_t element_size, bool (*compare)(const void *, const void *));

#endif
