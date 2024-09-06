#include <stdlib.h>
#include <string.h>
#include "../header/hashmap.h"


#define INITIAL_CAPACITY 16
#define LOAD_FACTOR 0.75

typedef struct HashNode {
    void *key;
    void *value;
    struct HashNode *next;
} HashNode;

struct HashMap {
    size_t key_size;
    size_t value_size;
    size_t capacity;
    size_t size;
    HashNode **buckets;
};

// Hash function (simple djb2 algorithm)
static size_t hash_function(const void *key, size_t key_size, size_t capacity) {
    unsigned long hash = 5381;
    const unsigned char *ptr = key;
    for (size_t i = 0; i < key_size; i++) {
        hash = ((hash << 5) + hash) + ptr[i];  // hash * 33 + ptr[i]
    }
    return hash % capacity;
}

// Create a new hash map with a specified key and value size
HashMap *hashmap_create(size_t key_size, size_t value_size, size_t capacity) {
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    if (!map) return NULL;

    map->key_size = key_size;
    map->value_size = value_size;
    map->capacity = capacity ? capacity : INITIAL_CAPACITY;
    map->size = 0;
    map->buckets = (HashNode **)calloc(map->capacity, sizeof(HashNode *));
    if (!map->buckets) {
        free(map);
        return NULL;
    }

    return map;
}

// Destroy the hash map and free its memory
void hashmap_destroy(HashMap *map) {
    if (!map) return;

    for (size_t i = 0; i < map->capacity; i++) {
        HashNode *node = map->buckets[i];
        while (node) {
            HashNode *next = node->next;
            free(node->key);
            free(node->value);
            free(node);
            node = next;
        }
    }

    free(map->buckets);
    free(map);
}

// Resize the hash map (rehashing all entries)
static bool hashmap_resize(HashMap *map, size_t new_capacity) {
    HashNode **new_buckets = (HashNode **)calloc(new_capacity, sizeof(HashNode *));
    if (!new_buckets) return false;

    // Rehash all nodes into the new buckets
    for (size_t i = 0; i < map->capacity; i++) {
        HashNode *node = map->buckets[i];
        while (node) {
            size_t new_index = hash_function(node->key, map->key_size, new_capacity);
            HashNode *next = node->next;

            node->next = new_buckets[new_index];
            new_buckets[new_index] = node;

            node = next;
        }
    }

    free(map->buckets);
    map->buckets = new_buckets;
    map->capacity = new_capacity;

    return true;
}

// Insert a key-value pair into the hash map
bool hashmap_insert(HashMap *map, const void *key, const void *value) {
    if (!map) return false;

    // Resize if the load factor is exceeded
    if ((double)map->size / map->capacity >= LOAD_FACTOR) {
        if (!hashmap_resize(map, map->capacity * 2)) return false;
    }

    size_t index = hash_function(key, map->key_size, map->capacity);
    HashNode *node = map->buckets[index];

    // Check if the key already exists
    while (node) {
        if (memcmp(node->key, key, map->key_size) == 0) {
            memcpy(node->value, value, map->value_size);
            return true;
        }
        node = node->next;
    }

    // Create a new node
    node = (HashNode *)malloc(sizeof(HashNode));
    if (!node) return false;

    node->key = malloc(map->key_size);
    node->value = malloc(map->value_size);
    if (!node->key || !node->value) {
        free(node->key);
        free(node->value);
        free(node);
        return false;
    }

    memcpy(node->key, key, map->key_size);
    memcpy(node->value, value, map->value_size);

    node->next = map->buckets[index];
    map->buckets[index] = node;
    map->size++;

    return true;
}

// Remove a key-value pair from the hash map
bool hashmap_remove(HashMap *map, const void *key) {
    if (!map) return false;

    size_t index = hash_function(key, map->key_size, map->capacity);
    HashNode *node = map->buckets[index];
    HashNode *prev = NULL;

    while (node) {
        if (memcmp(node->key, key, map->key_size) == 0) {
            if (prev) {
                prev->next = node->next;
            } else {
                map->buckets[index] = node->next;
            }

            free(node->key);
            free(node->value);
            free(node);
            map->size--;
            return true;
        }
        prev = node;
        node = node->next;
    }

    return false;
}

// Retrieve the value associated with a key
bool hashmap_get(const HashMap *map, const void *key, void *value) {
    if (!map) return false;

    size_t index = hash_function(key, map->key_size, map->capacity);
    HashNode *node = map->buckets[index];

    while (node) {
        if (memcmp(node->key, key, map->key_size) == 0) {
            memcpy(value, node->value, map->value_size);
            return true;
        }
        node = node->next;
    }

    return false;
}

// Check if a key exists in the hash map
bool hashmap_contains(const HashMap *map, const void *key) {
    if (!map) return false;

    size_t index = hash_function(key, map->key_size, map->capacity);
    HashNode *node = map->buckets[index];

    while (node) {
        if (memcmp(node->key, key, map->key_size) == 0) {
            return true;
        }
        node = node->next;
    }

    return false;
}

// Get the number of key-value pairs in the hash map
size_t hashmap_size(const HashMap *map) {
    return map ? map->size : 0;
}
