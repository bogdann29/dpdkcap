#include "hash_map.h"
#include "crc32.h"

void set_node(struct node *node, uint32_t key, uint32_t value)
{
    node->key = key;
    node->value = value;
    node->next = NULL;
}

void set_node128(struct node128 *node, __uint128_t key, __uint128_t value)
{
    node->key = key;
    node->value = value;
    node->next = NULL;
}

void map_initializer(struct hash_map *map)
{
    map->capacity = 10000;
    map->elem_count = 0;

    map->list = (struct node **)malloc(sizeof(struct node *) * map->capacity);
}

void map_initializer128(struct hash_map128 *map)
{
    map->capacity = 10000;
    map->elem_count = 0;

    map->list = (struct node128 **)malloc(sizeof(struct node128 *) * map->capacity);
}

uint32_t hash_function(uint32_t key, uint32_t dv)
{
    return (calculate_crc32c(0, (uint8_t *)&key, sizeof(key))) % dv;
}

uint32_t hash_function128(__uint128_t key, uint32_t dv)
{
    return (calculate_crc32c(0, (uint8_t *)&key, sizeof(key))) % dv;
}

void hash_insert(struct hash_map *map, uint32_t key, uint32_t value)
{
    uint32_t hash_idx = hash_function(key, map->capacity);
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    set_node(newNode, key, value);

    // no collision
    if (map->list[hash_idx] == NULL)
    {
        map->list[hash_idx] = newNode;
    }
    else
    {
        newNode->next = map->list[hash_idx];
        map->list[hash_idx] = newNode;
    }
}

void hash_insert128(struct hash_map128 *map, __uint128_t key, __uint128_t value)
{
    uint32_t hash_idx = hash_function(key, map->capacity);
    struct node128 *newNode = (struct node128 *)malloc(sizeof(struct node128));
    set_node128(newNode, key, value);

    // no collision
    if (map->list[hash_idx] == NULL)
    {
        map->list[hash_idx] = newNode;
    }
    else
    {
        newNode->next = map->list[hash_idx];
        map->list[hash_idx] = newNode;
    }
}

uint32_t hash_search(struct hash_map *map, uint32_t key)
{
    uint32_t hash_idx = hash_function(key, map->capacity);
    struct node *head = map->list[hash_idx];

    while (head != NULL)
    {
        if (head->key == key)
            return head->value;
        head = head->next;
    }

    return 0;
}

__uint128_t hash_search128(struct hash_map128 *map, __uint128_t key)
{
    uint32_t hash_idx = hash_function128(key, map->capacity);
    struct node128 *head = map->list[hash_idx];

    while (head != NULL)
    {
        if (head->key == key)
            return head->value;
        head = head->next;
    }

    return 0;
}
