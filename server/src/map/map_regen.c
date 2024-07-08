/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** map_regen.c
*/

#include "map_regen.h"
#include "execute_instructions_commands.h"

static void add_ressource_left(size_t *ressources, map_t *map)
{
    size_t *ressources_left[] = { &map->ressources_left->food,
    &map->ressources_left->linemate,
    &map->ressources_left->deraumere,
    &map->ressources_left->sibur,
    &map->ressources_left->mendiane,
    &map->ressources_left->phiras,
    &map->ressources_left->thystame };
    size_t *ressources_max[] = { &map->ressources_max->food,
    &map->ressources_max->linemate,
    &map->ressources_max->deraumere,
    &map->ressources_max->sibur,
    &map->ressources_max->mendiane,
    &map->ressources_max->phiras,
    &map->ressources_max->thystame };

    for (int i = 0; i < 7; i++) {
        *ressources_left[i] = MIN(*ressources_left[i] + ressources[i],
        *ressources_max[i]);
    }
}

static void ressource_left_logs(map_t *map)
{
    log_message("log/map.log", GREEN, "Resources have been regenerated.\n");
    log_message("log/map.log", GREEN, "Food : %ld\n",
        map->ressources_left->food);
    log_message("log/map.log", GREEN, "Linemate : %ld\n",
        map->ressources_left->linemate);
    log_message("log/map.log", GREEN, "Deraumere : %ld\n",
        map->ressources_left->deraumere);
    log_message("log/map.log", GREEN, "Sibur : %ld\n",
        map->ressources_left->sibur);
    log_message("log/map.log", GREEN, "Mendiane : %ld\n",
        map->ressources_left->mendiane);
    log_message("log/map.log", GREEN, "Phiras : %ld\n",
        map->ressources_left->phiras);
    log_message("log/map.log", GREEN, "Thystame : %ld\n",
        map->ressources_left->thystame);
}

static void add_ressources_back(size_t *ressources, map_t *map)
{
    distribute_resources(ressources[0], map, FOOD);
    distribute_resources(ressources[1], map, LINEMATE);
    distribute_resources(ressources[2], map, DERAUMERE);
    distribute_resources(ressources[3], map, SIBUR);
    distribute_resources(ressources[4], map, MENDIANE);
    distribute_resources(ressources[5], map, PHIRAS);
    distribute_resources(ressources[6], map, THYSTAME);
    ressource_left_logs(map);
    add_ressource_left(ressources, map);
}

static bool maximum_reached(size_t *ressources_max, map_t *map)
{
    if (map->ressources_left->food >= ressources_max[0] &&
        map->ressources_left->linemate >= ressources_max[1] &&
        map->ressources_left->deraumere >= ressources_max[2] &&
        map->ressources_left->sibur >= ressources_max[3] &&
        map->ressources_left->mendiane >= ressources_max[4] &&
        map->ressources_left->phiras >= ressources_max[5] &&
        map->ressources_left->thystame >= ressources_max[6])
        return true;
    return false;
}

void regenerate_map(game_t *game, map_t *map)
{
    ressources_t *ressources_max = map->ressources_max;

    map->missing_ressources = calculate_missing_ressources(map);
    if (maximum_reached((size_t[]){ressources_max->food,
        ressources_max->linemate, ressources_max->deraumere,
        ressources_max->sibur, ressources_max->mendiane,
        ressources_max->phiras, ressources_max->thystame}, map)) {
            log_message("log/map.log", GREEN, "Maximum ressources reached\n");
            return;
        }
    add_ressources_back((size_t[]){map->missing_ressources->food,
        map->missing_ressources->linemate, map->missing_ressources->deraumere,
        map->missing_ressources->sibur, map->missing_ressources->mendiane,
        map->missing_ressources->phiras, map->missing_ressources->thystame},
        map);
    regenerate_map_logs(game, map);
}

void debug_print_map(map_t *map)
{
    printf("Food : %ld\n", map->ressources_left->food);
    printf("Linemate : %ld\n", map->ressources_left->linemate);
    printf("Deraumere : %ld\n", map->ressources_left->deraumere);
    printf("Sibur : %ld\n", map->ressources_left->sibur);
    printf("Mendiane : %ld\n", map->ressources_left->mendiane);
    printf("Phiras : %ld\n", map->ressources_left->phiras);
    printf("Thystame : %ld\n", map->ressources_left->thystame);
}

void update_and_regenerate_map(zappy_t *zappy)
{
    server_t *server = (server_t *) zappy->server;

    if (server->game->timer_regen <= 0) {
        regenerate_map(server->game, server->map);
        zappy->server->game->timer_regen = 20 / zappy->server->game->freq;
        return;
    }
}
