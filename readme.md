
# Custom Data Structures and Algorithms Library

- **Stack**: LIFO data structure with push, pop, and visualization features.
- **Queue**: FIFO data structure with standard operations.
- **Sorting Algorithms**: Generic sorting functionality with custom comparison operators for ascending and descending order.
- **Search Algorithms**: Generic search functionality using custom iterators and comparison functions.
- **Hash Map**: A key-value data structure using a hash function for efficient lookups.

## File Structure

```bash
└── main.c
└── main.o
└── Libraries/
    ├── Stack.c
    ├── Queue.c
    ├── Hashmap.c
    ├── Search.c
    ├── Sorting.c
    ├── Stack.o
    ├── Queue.o
    ├── Hashmap.o
    ├── Search.o
    └── Sorting.o
headers/
    ├── Stack.h
    ├── Queue.h
    ├── Hashmap.h
    ├── Search.h
    └── Sorting.h
└── README.md
```


## compilation and exexution 

To compile and run the program:

Open a terminal in the project directory.
Run the following commands:
bash
Copy code
gcc -o main main.c stack.c queue.c sorting.c search.c hashmap.c graph.c -I.
./main
This will compile all the source files and generate an executable main. You can then run the program with the ./main command.

## Features
### Stack
Operations: Push, Pop
Visualization: Simple stack visualizer
### Queue
Operations: Enqueue, Dequeue
Visualization: Simple queue visualizer
### Sorting
Generic Sorting: Custom comparison function support for sorting in ascending or descending order.
### Searching
Generic Search: Custom iterator and comparison functions for searching in different data structures.
Hash Map
### Key-Value Store:
Efficient storage and retrieval using a hash function.
Resizable: Automatically resizes when the load factor exceeds a threshold.
Graph