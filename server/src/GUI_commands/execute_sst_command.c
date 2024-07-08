/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** execute_sst_command.c
*/

#include "execute_instructions_commands.h"

void execute_sst_command(player_info_t *player, char *instruction)
{
    zappy_t *myzappy = (zappy_t *)global_zappy;
    char *response = NULL;
    long int freq = 0;

    (void) player;
    sscanf(instruction, "sst %ld", &freq);
    if (freq <= 0) {
        send_data(myzappy->gui->fd, "sergerbp\n");
        return;
    }
    myzappy->server->game->freq = freq;
    new_alloc_asprintf(&response, "sst %ld\n", freq);
    send_data(myzappy->gui->fd, response);
}
