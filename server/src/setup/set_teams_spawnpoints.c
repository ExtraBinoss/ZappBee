/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** set_teams_spawnpoints
*/

#include "zappy.h"

void set_teams_spawnpoints(zappy_t *zappy)
{
    team_info_t *tmp = zappy->server->game->teams;

    while (tmp != NULL) {
        tmp->spawnpoint_x = rand() % zappy->server->game->width;
        tmp->spawnpoint_y = rand() % zappy->server->game->height;
        tmp = tmp->next;
    }
}
