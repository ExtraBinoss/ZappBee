/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** map_generation.h
*/

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "zappy.h"
#include "map_init.h"
typedef struct zappy_s zappy_t;
typedef struct tile_s tile_t;

typedef enum ressource_enum_s {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} ressource_enum_t;

typedef struct ressources_s {
    size_t food;
    size_t linemate;
    size_t deraumere;
    size_t sibur;
    size_t mendiane;
    size_t phiras;
    size_t thystame;
} ressources_t;

typedef struct tile_s {
    int id;
    ressources_t *tile_ressources;
    size_t egg;
    size_t x;
    size_t y;
    // tile_t *up;
    // tile_t *down;
    // tile_t *left;
    // tile_t *right;
    tile_t *next;
} tile_t;

typedef struct map_s {
    size_t width;
    size_t height;

    ressources_t *ressources_max;
    ressources_t *ressources_left;
    ressources_t *missing_ressources;

    size_t total_tiles;
    tile_t *tiles;
} map_t;

void generate_map(void);
void print_map(map_t *map);
int random_id(int id_max, int id_min);
ressources_t *calculate_missing_ressources(map_t *map);
void distribute_resources(size_t total_resources, map_t *map,
    ressource_enum_t resource);
