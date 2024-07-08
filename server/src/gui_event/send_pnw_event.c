/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** send_pnw_event.c
*/

#include "events.h"

void send_pnw_event(player_info_t *player)
{
    zappy_t *my_zappy = (zappy_t *)global_zappy;
    char *response = NULL;

    new_alloc_asprintf(&response, "pnw #%d %d %d %d %ld %s\n",
        player->fd, player->x,
        player->y, player->direction, player->level, player->team_name);
    send_data(my_zappy->gui->fd, response);
    log_message("log/pnw_event.log", GREEN, "pnw #%d %d %d %d %ld %s\n",
        player->fd, player->x, player->y, player->direction, player->level,
        player->team_name);
}
