#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>
#include <stdbool.h>

typedef struct HashMap HashMap;

// Create a new hash map with a specified key and value size
HashMap *hashmap_create(size_t key_size, size_t value_size, size_t capacity);

// Destroy the hash map and free its memory
void hashmap_destroy(HashMap *map);

// Insert a key-value pair into the hash map
bool hashmap_insert(HashMap *map, const void *key, const void *value);

// Remove a key-value pair from the hash map
bool hashmap_remove(HashMap *map, const void *key);

// Retrieve the value associated with a key
bool hashmap_get(const HashMap *map, const void *key, void *value);

// Check if a key exists in the hash map
bool hashmap_contains(const HashMap *map, const void *key);

// Get the number of key-value pairs in the hash map
size_t hashmap_size(const HashMap *map);

#endif
