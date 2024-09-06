#include <stdio.h>
#include "../header/sorting.h"


// Comparison function for ascending order (integers)
int compare_asc(const void *a, const void *b) {
    int int_a = *(int *)a;
    int int_b = *(int *)b;
    return (int_a > int_b) - (int_a < int_b);  // Returns -1, 0, or 1
}

// Comparison function for descending order (integers)
int compare_desc(const void *a, const void *b) {
    int int_a = *(int *)a;
    int int_b = *(int *)b;
    return (int_b > int_a) - (int_b < int_a);  // Reverse comparison
}

// int main() {
//     int arr[] = {5, 3, 8, 4, 2};
//     size_t length = sizeof(arr) / sizeof(arr[0]);

//     // Sort in ascending order
//     sort(arr, sizeof(int), length, compare_asc);
//     printf("Ascending: ");
//     for (size_t i = 0; i < length; i++) {
//         printf("%d ", arr[i]);
//     }
//     printf("\n");

//     // Sort in descending order
//     sort(arr, sizeof(int), length, compare_desc);
//     printf("Descending: ");
//     for (size_t i = 0; i < length; i++) {
//         printf("%d ", arr[i]);
//     }
//     printf("\n");

//     return 0;
// }
