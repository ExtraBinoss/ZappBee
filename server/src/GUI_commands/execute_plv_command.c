/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** execute_plv_command.c
*/

#include "execute_instructions_commands.h"

void execute_plv_command(player_info_t *player, char *instruction)
{
    zappy_t *myzappy = (zappy_t *)global_zappy;
    player_info_t *player_to_find = NULL;
    char *response = NULL;
    int fd = 0;

    (void)player;
    sscanf(instruction, "plv #%d", &fd);
    player_to_find = find_player_by_fd(myzappy->server->game->players, fd);
    if (player_to_find == NULL) {
        remove_from_garbage(response);
        return;
    }
    new_alloc_asprintf(&response, "plv #%d %ld\n", player_to_find->fd,
        player_to_find->level);
    send_data(myzappy->gui->fd, response);
    remove_from_garbage(response);
}
