#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For sleep()
#include "header/stack.h"
#include "header/queue.h"
#include "header/sorting.h"
#include "header/search.h"
#include "header/hashmap.h"

// Delay for animation
#define ANIMATION_DELAY 1

// Comparison functions
int compare_ascending(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int compare_descending(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}
// Function to compare integers for search
bool compare_ints(const void *a, const void *b) {
    return *(int *)a == *(int *)b;
}

// Function to print a separator line
void print_separator() {
    printf("\n------------------------------------------\n");
    sleep(ANIMATION_DELAY);
}

// Function to print the current stack elements with animation
void print_stack(Stack *stack) {
    printf("| Current Stack: ");
    if (stack_is_empty(stack)) {
        printf("Empty");
    } else {
        for (size_t i = 0; i < stack_size(stack); i++) {
            int element;
            stack_peek_nth(stack, i, &element);  // Accessing nth element
            printf("%d ", element);
        }
    }
    printf("|\n");
    sleep(ANIMATION_DELAY);  // Adding delay to simulate animation
}
void print_array(int *array, size_t length) {
    printf("Array: ");
    for (size_t i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
// Function to print the current queue elements with animation
void print_queue(Queue *queue) {
    printf("| Current Queue: ");

    if (queue_is_empty(queue)) {
        printf("Empty");
    } else {
        size_t size = queue_size(queue);
        
        // Print each element using queue_peek_nth
        for (size_t i = 0; i < size; i++) {
            int element;
            queue_peek_nth(queue, i, &element);  // Access the i-th element without dequeuing
            printf("%d ", element);  // Print the element
        }
    }

    printf("|\n");
    sleep(ANIMATION_DELAY);  // Adding delay to simulate animation
}


void stack_operations() {
    Stack *stack = stack_create(sizeof(int));
    if (!stack) {
        printf("Failed to create stack.\n");
        return;
    }

    printf("Starting to Push Elements:\n");
    print_separator();
    int arr[] = {10, 20, 30, 40, 50};

    for (int i = 0; i < 5; i++) {
        printf("| Pushing %d onto the stack |\n", arr[i]);
        stack_push(stack, &arr[i]);
        printf("| Stack Size: %ld |\n", stack_size(stack));
        printf("| Is Empty? %s |\n", stack_is_empty(stack) ? "Yes" : "No");
        print_stack(stack);
        print_separator();
    }

    printf("Starting to Pop Elements:\n");
    print_separator();

    while (!stack_is_empty(stack)) {
        int top_element;
        stack_peek(stack, &top_element);
        printf("| Popping %d from the stack |\n", top_element);
        stack_pop(stack);
        printf("| Stack Size: %ld |\n", stack_size(stack));
        printf("| Is Empty? %s |\n", stack_is_empty(stack) ? "Yes" : "No");
        print_stack(stack);
        print_separator();
    }

    stack_destroy(stack);
    printf("Stack destroyed and memory freed.\n");
    print_separator();
}

void queue_operations() {
    Queue *queue = queue_create(sizeof(int));
    if (!queue) {
        printf("Failed to create queue.\n");
        return;
    }

    printf("Starting to Enqueue Elements:\n");
    print_separator();
    int arr[] = {10, 20, 30, 40, 50};

    for (int i = 0; i < 5; i++) {
        printf("| Enqueuing %d into the queue |\n", arr[i]);
        queue_enqueue(queue, &arr[i]);
        printf("| Queue Size: %ld |\n", queue_size(queue));
        printf("| Is Empty? %s |\n", queue_is_empty(queue) ? "Yes" : "No");
        print_queue(queue);
        print_separator();
    }

    printf("Starting to Dequeue Elements:\n");
    print_separator();

    while (!queue_is_empty(queue)) {
        int front_element;
        queue_peek(queue, &front_element);
        printf("| Dequeuing %d from the queue |\n", front_element);
        queue_dequeue(queue);
        printf("| Queue Size: %ld |\n", queue_size(queue));
        printf("| Is Empty? %s |\n", queue_is_empty(queue) ? "Yes" : "No");
        print_queue(queue);
        print_separator();
    }

    queue_destroy(queue);
    printf("Queue destroyed and memory freed.\n");
    print_separator();
}

void sort_operations() {
    int choice;
    size_t length = 5;
    int array[] = {40, 10, 30, 20, 50};

    while (1) {
        printf("Sort Menu:\n");
        printf("1. Sort Ascending\n");
        printf("2. Sort Descending\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                sort(array, sizeof(int), length, compare_ascending);
                printf("Sorted in Ascending Order:\n");
                print_array(array, length);
                break;
            case 2:
                sort(array, sizeof(int), length, compare_descending);
                printf("Sorted in Descending Order:\n");
                print_array(array, length);
                break;
            case 3:
                return; // Go back to the main menu
            default:
                printf("Invalid choice. Please enter a number between 1 and 3.\n");
                break;
        }
    }
}

bool array_iterator(void *array, size_t index, void *element) {
    int *int_array = (int *)array;
    *(int *)element = int_array[index];
    return true;
}


// Search operations menu
void search_operations() {
    int array[] = {40, 10, 30, 50, 20};
    size_t length = sizeof(array) / sizeof(array[0]);
    int target;
    print_array(array,length);
    printf("Enter the element to search: ");
    scanf("%d", &target);

    bool found = search(array, array_iterator, length, &target, sizeof(int), compare_ints);
    if (found) {
        printf("Element %d found in the array.\n", target);
    } else {
        printf("Element %d not found in the array.\n", target);
    }

    print_separator();
}

void hashmap_operations() {
    HashMap *map = hashmap_create(sizeof(int), sizeof(int), 0);
    if (!map) {
        printf("Failed to create hash map.\n");
        return;
    }

    int keys[] = {1, 2, 3, 4, 5};
    int values[] = {100, 200, 300, 400, 500};

    printf("Inserting key-value pairs into the hash map:\n");
    for (int i = 0; i < 5; i++) {
        if (hashmap_insert(map, &keys[i], &values[i])) {
            printf("Inserted key %d with value %d\n", keys[i], values[i]);
        } else {
            printf("Failed to insert key %d\n", keys[i]);
        }
        print_separator();
    }

    // Retrieving and printing values
    int value;
    for (int i = 0; i < 5; i++) {
        if (hashmap_get(map, &keys[i], &value)) {
            printf("Retrieved value for key %d: %d\n", keys[i], value);
        } else {
            printf("Key %d not found in hash map\n", keys[i]);
        }
        print_separator();
    }

    // Removing key-value pairs
    printf("Removing key 3 from the hash map:\n");
    if (hashmap_remove(map, &keys[2])) {
        printf("Key 3 removed successfully.\n");
    } else {
        printf("Failed to remove key 3.\n");
    }
    print_separator();

    printf("Checking if key 3 is still in the hash map:\n");
    if (hashmap_contains(map, &keys[2])) {
        printf("Key 3 is still present.\n");
    } else {
        printf("Key 3 is not present.\n");
    }
    print_separator();

    hashmap_destroy(map);
    printf("Hash map destroyed.\n");
}

int main() {
    int choice;

    while (1) {
        printf("Menu:\n");
        printf("1. Stack Operations\n");
        printf("2. Queue Operations\n");
        printf("3. Sorting Operations\n");
        printf("4. Search Operations\n");
        printf("5. Hash Map Operations\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        print_separator();

        switch (choice) {
            case 1:
                stack_operations();
                break;
            case 2:
                queue_operations();
                break;
            case 3:
                sort_operations();
                break;
            case 4:
                search_operations();
                break;
            case 5:
                hashmap_operations();
                break;
            case 6:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
                print_separator();
                break;
        }
    }

    return 0;
}