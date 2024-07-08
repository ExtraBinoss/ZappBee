/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** execute_ppo_command.c
*/

#include "execute_instructions_commands.h"

void execute_ppo_command(player_info_t *player, char *instruction)
{
    zappy_t *myzappy = (zappy_t *)global_zappy;
    player_info_t *player_to_find = NULL;
    char *response = NULL;
    int fd = 0;

    (void)player;
    sscanf(instruction, "ppo #%d", &fd);
    player_to_find = find_player_by_fd(myzappy->server->game->players, fd);
    if (player_to_find == NULL) {
        send_data(myzappy->gui->fd, "sbp\n");
        return;
    }
    new_alloc_asprintf(&response, "ppo #%d %d %d %d\n", player_to_find->fd,
        player_to_find->x, player_to_find->y, player_to_find->direction);
    send_data(myzappy->gui->fd, response);
    log_message("log/ppo.log", GREEN, "ppo #%d %d %d %d\n", player_to_find->fd,
        player_to_find->x, player_to_find->y, player_to_find->direction);
}
