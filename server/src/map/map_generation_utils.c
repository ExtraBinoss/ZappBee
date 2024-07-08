/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** map_generation_utils.c
*/

#include "map_generation.h"

void print_map(map_t *map)
{
    tile_t *tile = map->tiles;

    dprintf(1, "map->height : %lu\n", map->height);
    printf("map->width : %lu\n", map->width);
    while (tile != NULL) {
        printf("tile[%lu][%lu] :\n", tile->x, tile->y);
        printf("food : %ld\n", tile->tile_ressources->food);
        printf("linemate : %ld\n", tile->tile_ressources->linemate);
        printf("deraumere : %ld\n", tile->tile_ressources->deraumere);
        printf("sibur : %ld\n", tile->tile_ressources->sibur);
        printf("mendiane : %ld\n", tile->tile_ressources->mendiane);
        printf("phiras : %ld\n", tile->tile_ressources->phiras);
        printf("thystame : %ld\n", tile->tile_ressources->thystame);
        tile = tile->next;
    }
}

int random_id(int id_max, int id_min)
{
    return (rand() % (id_max - id_min + 1)) + id_min;
}

ressources_t *calculate_missing_ressources(map_t *map)
{
    ressources_t *r_left = map->ressources_left;
    ressources_t *r_max = map->ressources_max;

    map->missing_ressources->food = r_max->food > r_left->food ?
        r_max->food - r_left->food : 0;
    map->missing_ressources->linemate = r_max->linemate > r_left->linemate ?
        r_max->linemate - r_left->linemate : 0;
    map->missing_ressources->deraumere = r_max->deraumere > r_left->deraumere ?
        r_max->deraumere - r_left->deraumere : 0;
    map->missing_ressources->sibur = r_max->sibur > r_left->sibur ?
        r_max->sibur - r_left->sibur : 0;
    map->missing_ressources->mendiane = r_max->mendiane > r_left->mendiane ?
        r_max->mendiane - r_left->mendiane : 0;
    map->missing_ressources->phiras = r_max->phiras > r_left->phiras ?
        r_max->phiras - r_left->phiras : 0;
    map->missing_ressources->thystame = r_max->thystame > r_left->thystame ?
        r_max->thystame - r_left->thystame : 0;
    return map->missing_ressources;
}
