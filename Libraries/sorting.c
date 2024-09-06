#include <stdlib.h>
#include <string.h>
#include "../header/sorting.h"


// Swap two elements in memory
static void swap(void *a, void *b, size_t element_size) {
    void *temp = malloc(element_size);
    if (temp) {
        memcpy(temp, a, element_size);
        memcpy(a, b, element_size);
        memcpy(b, temp, element_size);
        free(temp);
    }
}

// Partition function for quicksort
static size_t partition(void *array, size_t element_size, size_t low, size_t high, CompareFunc cmp) {
    void *pivot = (char *)array + high * element_size;
    size_t i = low;

    for (size_t j = low; j < high; j++) {
        void *current = (char *)array + j * element_size;
        if (cmp(current, pivot) < 0) {
            swap((char *)array + i * element_size, current, element_size);
            i++;
        }
    }
    swap((char *)array + i * element_size, pivot, element_size);
    return i;
}

// Quicksort recursive function
static void quicksort(void *array, size_t element_size, size_t low, size_t high, CompareFunc cmp) {
    if (low < high) {
        size_t pivot_index = partition(array, element_size, low, high, cmp);
        if (pivot_index > 0) {
            quicksort(array, element_size, low, pivot_index - 1, cmp);
        }
        quicksort(array, element_size, pivot_index + 1, high, cmp);
    }
}

// Sort function that uses quicksort
void sort(void *array, size_t element_size, size_t length, CompareFunc cmp) {
    if (length > 1) {
        quicksort(array, element_size, 0, length - 1, cmp);
    }
}
