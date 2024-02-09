#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct node
{
    uint32_t key;   // old_ip_4
    uint32_t value; // new_ip_4
    struct node *next;
};

struct node128
{
    __uint128_t key;   // old_ip_6
    __uint128_t value; // new_ip_6
    struct node128 *next;
};

/**
 * @brief Set the node object
 *
 * @param node
 * @param key old_ip
 * @param value new_ip
 */
void set_node(struct node *node, uint32_t key, uint32_t value);

/**
 * @brief Set the node object
 *
 * @param node
 * @param key old_ip_6
 * @param value new_ip_6
 */
void set_node128(struct node128 *node, __uint128_t key, __uint128_t value);

struct hash_map
{
    uint32_t elem_count;
    uint32_t capacity;
    struct node **list;
};

struct hash_map128
{
    uint32_t elem_count;
    uint32_t capacity;
    struct node128 **list;
};

/**
 * @brief map constructor
 *
 * @param map s
 */
void map_initializer(struct hash_map *map);

/**
 * @brief map128 constructor
 *
 * @param map
 */
void map_initializer128(struct hash_map128 *map);

/**
 * @brief hash calculating by key
 *
 * @param key
 * @param dv
 * @return uint32_t
 */
uint32_t hash_function(uint32_t key, uint32_t dv);

/**
 * @brief hash calculating by key
 *
 * @param key
 * @param dv
 * @return uint32_t
 */
uint32_t hash_function128(__uint128_t key, uint32_t dv);

/**
 * @brief inserting element {key, value} into hash_map map
 *
 * @param map
 * @param key
 * @param value
 */
void hash_insert(struct hash_map *map, uint32_t key, uint32_t value);

/**
 * @brief inserting element {key, value} into hash_map128 map
 *
 * @param map
 * @param key
 * @param value
 */
void hash_insert128(struct hash_map128 *map, __uint128_t key, __uint128_t value);

/**
 * @brief searching element by key in hash_map map
 *
 * @param map
 * @param key
 * @return uint32_t s
 */
uint32_t hash_search(struct hash_map *map, uint32_t key);

/**
 * @brief searching element by key in hash_map128 map
 *
 * @param map
 * @param key
 * @return __uint128_t
 */
__uint128_t hash_search128(struct hash_map128 *map, __uint128_t key);

#endif