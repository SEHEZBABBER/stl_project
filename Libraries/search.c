#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include "../header/search.h"


// Generic search function implementation
bool search(void *data_structure, IteratorFunc iterator, size_t size, const void *target, size_t element_size, bool (*compare)(const void *, const void *)) {
    // Iterate over the data structure
    for (size_t i = 0; i < size; i++) {
        void *element = malloc(element_size);
        if (!element) {
            // Handle memory allocation failure
            return false;
        }

        // Use the iterator function to retrieve the element at index 'i'
        if (iterator(data_structure, i, element)) {
            // Use the compare function to check if the element matches the target
            if (compare(element, target)) {
                free(element);  // Free the allocated memory
                return true;    // Element found
            }
        } else {
            // If the iterator fails to retrieve an element, stop the search
            free(element);  // Free the allocated memory
            return false;
        }

        free(element);  // Free the allocated memory
    }
    
    // If no match was found, return false
    return false;
}