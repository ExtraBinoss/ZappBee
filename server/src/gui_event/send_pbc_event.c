/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** send_pbc_event.c
*/

#include "events.h"

void send_pbc_event(player_info_t *player, char *cmd)
{
    zappy_t *my_zappy = (zappy_t *)global_zappy;
    char *message = NULL;

    new_alloc_asprintf(&message, "pbc #%d %s\n", player->fd, cmd);
    send_data(my_zappy->gui->fd, message);
    log_message("log/pbc_event.log", GREEN, "pbc #%d %s\n", player->fd, cmd);
}
