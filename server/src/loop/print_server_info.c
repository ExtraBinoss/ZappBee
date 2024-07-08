/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** print_server_info.c
*/

#include "print_server_info.h"

void print_teams(team_info_t *teams)
{
    team_info_t *current_team = teams;
    int count = 0;

    printf("------------------------------------------------ \n");
    printf("Teams Info:\n");
    printf("------------------------------------------------ \n");
    printf(" teams = \n");
    while (current_team) {
        if (current_team->name != NULL) {
            printf(" - %s\n", current_team->name);
            count++;
        }
        current_team = current_team->next;
    }
    printf(" Total teams: %d\n", count);
}

void print_beginning_info(zappy_t *zappy)
{
    printf("================================================= \n");
    printf("                  Zappy Server                    \n");
    printf(" ------------------------------------------------ \n");
    printf("Arguments:\n");
    printf(" - port = %d\n",
        zappy->server->port);
    printf(" - map_width = %d\n",
        zappy->server->game->width);
    printf(" - map_height = %d\n",
        zappy->server->game->height);
    printf(" - clients_nb = %d\n",
        zappy->server->game->clientsNb);
    printf(" - freq = %f\n",
        zappy->server->game->freq);
    print_teams(zappy->server->game->teams);
    printf("================================================= \n");
}
