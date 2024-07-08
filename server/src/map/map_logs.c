/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** map_logs.c
*/

#include "log.h"

void regenerate_map_logs(game_t *game, map_t *map)
{
    log_message("log/map.log", GREEN, "Resources have been regenerated.\n");
    log_message("log/map.log", GREEN, "Time until next regeneration : %f\n",
        game->timer_regen);
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
