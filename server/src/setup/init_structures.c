/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** init_structures.c
*/

#include "zappy.h"

team_info_t *init_team_struct(void)
{
    team_info_t *new_team = new_alloc(sizeof(team_info_t));

    new_team->name = NULL;
    new_team->slotAvailable = 0;
    new_team->slotMax = 0;
    new_team->spawnpoint_x = 0;
    new_team->spawnpoint_y = 0;
    new_team->eggs = NULL;
    new_team->next = NULL;
    return new_team;
}

void init_server_struct(zappy_t *zappy)
{
    zappy->server = new_alloc(sizeof(server_t));
    zappy->server->game = new_alloc(sizeof(game_t));
    zappy->server->game->teams = NULL;
    zappy->server->map = new_alloc(sizeof(map_t));
    zappy->server->port = 0;
    zappy->server->game->width = 0;
    zappy->server->game->height = 0;
    zappy->server->game->clientsNb = 0;
    zappy->server->game->freq = 0;
    zappy->server->game->timer_regen = 0;
    zappy->server->game->egg_max_id = 0;
    zappy->server->game->players = NULL;
    zappy->server->stimeout.tv_sec = 0;
    zappy->server->stimeout.tv_usec = 0;
    zappy->server->win_time = time(NULL);
    zappy->server->processor_time = 0;
}

void init_gui_struct(zappy_t *zappy)
{
    zappy->gui = new_alloc(sizeof(gui_t));
    zappy->gui->fd = -1;
    zappy->gui->stack = NULL;
}

void init_ia_struct(zappy_t *zappy)
{
    zappy->IA = new_alloc(sizeof(ia_t));
    zappy->IA->clients = NULL;
}

void init_all_struct(zappy_t *zappy)
{
    init_server_struct(zappy);
    init_gui_struct(zappy);
    init_ia_struct(zappy);
}
