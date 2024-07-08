/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** send_pdi_event.c
*/

#include "events.h"

void send_pdi_event(player_info_t *player)
{
    zappy_t *my_zappy = (zappy_t *)global_zappy;
    char *response = NULL;

    new_alloc_asprintf(&response, "pdi #%d\n", player->fd);
    send_data(my_zappy->gui->fd, response);
}
