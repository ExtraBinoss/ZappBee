/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** execute_tna_command.c
*/

#include "execute_instructions_commands.h"

void execute_tna_command(player_info_t *player, char *instruction)
{
    zappy_t *myzappy = (zappy_t *)global_zappy;
    team_info_t *team = myzappy->server->game->teams;
    char *response = NULL;

    (void)instruction;
    (void)player;
    while (team) {
        if (team->name == NULL)
            return;
        new_alloc_asprintf(&response, "tna %s\n", team->name);
        send_data(myzappy->gui->fd, response);
        team = team->next;
    }
}
