/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** execute_instructions_command.c
*/

#include "execute_instructions_commands.h"

void execute_msz_command(player_info_t *player, char *instruction)
{
    zappy_t *myzappy = (zappy_t *)global_zappy;
    game_t *game = myzappy->server->game;
    gui_t *gui = myzappy->gui;
    char *response = NULL;

    (void)player;
    (void)instruction;
    new_alloc_asprintf(&response, "msz %d %d\n", game->width, game->height);
    send_data(gui->fd, response);
}
