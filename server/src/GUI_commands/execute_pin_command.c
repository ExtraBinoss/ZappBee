/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** execute_pin_command.c
*/

#include "execute_instructions_commands.h"

static bool player_send_sbp(player_info_t *player_to_find, zappy_t *myzappy)
{
    if (player_to_find == NULL) {
        send_data(myzappy->gui->fd, "sbp\n");
        return true;
    }
    return false;
}

void execute_pin_command(player_info_t *player, char *instruction)
{
    zappy_t *myzappy = (zappy_t *)global_zappy;
    player_info_t *player_to_find = NULL;
    char *resp = NULL;
    int fd = 0;

    (void)player;
    sscanf(instruction, "pin #%d", &fd);
    player_to_find = find_player_by_fd(myzappy->server->game->players, fd);
    if (player_send_sbp(player_to_find, myzappy) == true)
        return;
    new_alloc_asprintf(&resp, "pin #%d %d %d %lu %lu %lu %lu %lu %lu %lu\n",
        player_to_find->fd,
        player_to_find->x, player_to_find->y, player_to_find->inventory->food,
        player_to_find->inventory->linemate,
        player_to_find->inventory->deraumere,
        player_to_find->inventory->sibur, player_to_find->inventory->mendiane,
        player_to_find->inventory->phiras,
        player_to_find->inventory->thystame);
    send_data(myzappy->gui->fd, resp);
}
