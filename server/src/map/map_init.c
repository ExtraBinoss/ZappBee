/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** map_init.c
*/

#include "map_init.h"

static ressources_t *ressources_init(void)
{
    ressources_t *ressources = new_alloc(sizeof(ressources_t));

    ressources->food = 0;
    ressources->linemate = 0;
    ressources->deraumere = 0;
    ressources->sibur = 0;
    ressources->mendiane = 0;
    ressources->phiras = 0;
    ressources->thystame = 0;
    return ressources;
}

void setup_map(void)
{
    server_t *myzappy = (server_t *) global_zappy->server;

    myzappy->map->width = myzappy->game->width;
    myzappy->map->height = myzappy->game->height;
    myzappy->map->tiles = NULL;
    myzappy->map->total_tiles = myzappy->map->width * myzappy->map->height;
    myzappy->map->ressources_max = ressources_init();
    myzappy->map->ressources_left = ressources_init();
    myzappy->map->missing_ressources = ressources_init();
}

void init_tiles(tile_t *tile, int tile_id, size_t x, size_t y)
{
    tile->tile_ressources = new_alloc(sizeof(ressources_t));
    tile->tile_ressources->food = 0;
    tile->tile_ressources->linemate = 0;
    tile->tile_ressources->deraumere = 0;
    tile->tile_ressources->sibur = 0;
    tile->tile_ressources->mendiane = 0;
    tile->tile_ressources->phiras = 0;
    tile->tile_ressources->thystame = 0;
    tile->egg = 0;
    tile->id = tile_id;
    tile->x = x;
    tile->y = y;
}
