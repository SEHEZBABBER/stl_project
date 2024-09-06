#ifndef SORT_H
#define SORT_H

#include <stddef.h>

// Comparison function type definition
typedef int (*CompareFunc)(const void *, const void *);

// Sorts an array using the provided comparison function
void sort(void *array, size_t element_size, size_t length, CompareFunc cmp);

#endif
