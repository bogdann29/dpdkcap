#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * @file hash_map.h
 * @brief Definition of hash map data structure and its associated functions
 *
 */

/**
 * @struct node
 * @brief Structure representing a node containing a key and a value (32 bits)
 */
struct node
{
    uint32_t key;      /**< Key of the node representing old IPv4 */
    uint32_t value;    /**< Value of the node representing new IPv4 */
    struct node *next; /**< Pointer to the next node in the linked list */
};

/**
 * @struct node128
 * @brief Structure representing a node containing a key and a value (128 bits)
 */
struct node128
{
    __uint128_t key;      /**< Key of the node representing old IPv6 */
    __uint128_t value;    /**< Value of the node representing new IPv6 */
    struct node128 *next; /**< Pointer to the next node in the linked list */
};

/**
 * @brief Assign a key and value to a node object
 * @param node Pointer to the node struct
 * @param key Old IPv4 to be assigned to the node
 * @param value New IPv4 to be assigned to the node
 */
void set_node(struct node *node, uint32_t key, uint32_t value);

/**
 * @brief Assign a key and value to a node object with 128-bit keys and values
 * @param node Pointer to the node128 struct
 * @param key Old IPv6 to be assigned to the node
 * @param value New IPv6 to be assigned to the node
 */
void set_node128(struct node128 *node, __uint128_t key, __uint128_t value);

/**
 * @struct hash_map
 * @brief Basic hash map with 32-bit keys and values
 */
struct hash_map
{
    uint32_t elem_count; /**< Number of elements in the hash map */
    uint32_t capacity;   /**< Capacity of the hash map */
    struct node **list;  /**< Array of linked list nodes */
};

/**
 * @struct hash_map128
 * @brief Larger hash map with 128-bit keys and values
 */
struct hash_map128
{
    uint32_t elem_count;   /**< Number of elements in the hash map */
    uint32_t capacity;     /**< Capacity of the hash map */
    struct node128 **list; /**< Array of linked list nodes */
};

/**
 * @brief Initialize a hash map with 32-bit keys and values
 * @param map Pointer to the hash_map struct to be initialized
 */
void map_initializer(struct hash_map *map);

/**
 * @brief Initialize a larger hash map with 128-bit keys and values
 * @param map Pointer to the hash_map128 struct to be initialized
 */
void map_initializer128(struct hash_map128 *map);

/**
 * @brief Calculate the hash value of a 32-bit key
 * @param key The input key
 * @param dv The divisor used for calculating the hash value
 * @return The calculated hash value
 */
uint32_t hash_function(uint32_t key, uint32_t dv);

/**
 * @brief Calculate the hash value of a 128-bit key
 * @param key The input key
 * @param dv The divisor used for calculating the hash value
 * @return The calculated hash value
 */
uint32_t hash_function128(__uint128_t key, uint32_t dv);

/**
 * @brief Insert a key-value pair into a hash map with 32-bit keys and values
 * @param map Pointer to the hash_map struct
 * @param key The key to be inserted
 * @param value The value associated with the key
 */
void hash_insert(struct hash_map *map, uint32_t key, uint32_t value);

/**
 * @brief Insert a key-value pair into a larger hash map with 128-bit keys and values
 * @param map Pointer to the hash_map128 struct
 * @param key The key to be inserted
 * @param value The value associated with the key
 */
void hash_insert128(struct hash_map128 *map, __uint128_t key, __uint128_t value);

/**
 * @brief Search for the value associated with a key in a hash map with 32-bit keys and values
 * @param map Pointer to the hash_map struct
 * @param key The key to search for
 * @return The value associated with the key
 */
uint32_t hash_search(struct hash_map *map, uint32_t key);

/**
 * @brief Search for the value associated with a key in a larger hash map with 128-bit keys and values
 * @param map Pointer to the hash_map128 struct
 * @param key The key to search for
 * @return The value associated with the key
 */
__uint128_t hash_search128(struct hash_map128 *map, __uint128_t key);

#endif