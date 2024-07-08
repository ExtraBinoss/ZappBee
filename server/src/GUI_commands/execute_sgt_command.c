/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** execute_server_get_time.command.c
*/

#include "execute_instructions_commands.h"

void execute_sgt_command(player_info_t *player, char *instruction)
{
    zappy_t *myzappy = (zappy_t *)global_zappy;
    char *response = NULL;

    (void)instruction;
    (void)player;
    new_alloc_asprintf(&response, "sgt %f\n", myzappy->server->game->freq);
    send_data(myzappy->gui->fd, response);
    log_message("log/sgt.log", GREEN, "sgt %f\n", myzappy->server->game->freq);
}
