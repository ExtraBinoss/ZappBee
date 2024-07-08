/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** map_generation.c
*/

#include "map_generation.h"
#include "log.h"
#include "network_transactions.h"
#include "execute_instructions_commands.h"
#include <math.h>
#include <limits.h>

static tile_t *find_tile(map_t *map, int id)
{
    tile_t *tile = map->tiles;

    while (tile != NULL) {
        if (tile->id == id) {
            return tile;
        }
        tile = tile->next;
    }
    return NULL;
}

static void increment_resource(tile_t *tile, ressource_enum_t resource)
{
    if (tile == NULL) {
        return;
    }
    if (resource == FOOD)
        tile->tile_ressources->food++;
    if (resource == LINEMATE)
        tile->tile_ressources->linemate++;
    if (resource == DERAUMERE)
        tile->tile_ressources->deraumere++;
    if (resource == SIBUR)
        tile->tile_ressources->sibur++;
    if (resource == MENDIANE)
        tile->tile_ressources->mendiane++;
    if (resource == PHIRAS)
        tile->tile_ressources->phiras++;
    if (resource == THYSTAME)
        tile->tile_ressources->thystame++;
}

static void increment_resource_on_tile(map_t *map, int id,
    ressource_enum_t resource)
{
    char *message = NULL;
    tile_t *tile = find_tile(map, id);

    if (tile == NULL) {
        return;
    }
    increment_resource(tile, resource);
    new_alloc_asprintf(&message, "bct %ld %ld\n", tile->x, tile->y);
    execute_bct_command(NULL, message);
}

void distribute_resources(size_t total_resources,
    map_t *map, ressource_enum_t resource)
{
    int id = 0;

    for (size_t i = 0; i < total_resources; i++) {
        id = random_id(map->total_tiles, 0);
        increment_resource_on_tile(map, id, resource);
    }
}

static void setup_ressources_left(map_t *map)
{
    map->ressources_left->food = map->ressources_max->food;
    map->ressources_left->linemate = map->ressources_max->linemate;
    map->ressources_left->deraumere = map->ressources_max->deraumere;
    map->ressources_left->sibur = map->ressources_max->sibur;
    map->ressources_left->mendiane = map->ressources_max->mendiane;
    map->ressources_left->phiras = map->ressources_max->phiras;
    map->ressources_left->thystame = map->ressources_max->thystame;
}

// resources need to be spread evenly on the map
//resource density :
// food : 0.5
// linemate : 0.3
// deraumere : 0.15
// sibur : 0.1
// mendiane : 0.1
// phiras : 0.08
// thystame : 0.05
void create_ressources(map_t *map)
{
    map->ressources_max->food = map->total_tiles * 0.5;
    map->ressources_max->linemate = map->total_tiles * 0.3;
    map->ressources_max->deraumere = map->total_tiles * 0.15;
    map->ressources_max->sibur = map->total_tiles * 0.1;
    map->ressources_max->mendiane = map->total_tiles * 0.1;
    map->ressources_max->phiras = map->total_tiles * 0.08;
    map->ressources_max->thystame = map->total_tiles * 0.05;
    distribute_resources(map->ressources_max->food, map, FOOD);
    distribute_resources(map->ressources_max->linemate, map, LINEMATE);
    distribute_resources(map->ressources_max->deraumere, map, DERAUMERE);
    distribute_resources(map->ressources_max->sibur, map, SIBUR);
    distribute_resources(map->ressources_max->mendiane, map, MENDIANE);
    distribute_resources(map->ressources_max->phiras, map, PHIRAS);
    distribute_resources(map->ressources_max->thystame, map, THYSTAME);
    setup_ressources_left(map);
    log_message("log/map.log", GREEN, "Resources have been created.\n");
}

/**
 * Generates the game map.
 * This function initializes the map, creates tiles, sets up resources,
 * Some functions are implemented to help with the map in general.
 * remove_some_ressources: removes some ressources from the map (debug)
 * regenerate_map: regenerates the map by adding the needed ressources
 * print_map: prints the map (debug)
 * @param void
 */
void generate_map(void)
{
    server_t *myzappy = (server_t *) global_zappy->server;
    tile_t *tile = NULL;
    int tile_id = 0;

    myzappy->game->timer_regen = 20 / myzappy->game->freq;
    setup_map();
    for (size_t i = 0; i < myzappy->map->width; i++) {
        for (size_t j = 0; j < myzappy->map->height; j++) {
            tile = new_alloc(sizeof(tile_t));
            init_tiles(tile, tile_id, i, j);
            tile_id++;
            tile->next = myzappy->map->tiles;
            myzappy->map->tiles = tile;
        }
    }
    create_ressources(myzappy->map);
}
