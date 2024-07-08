/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** send_pdr_event.c
*/

#include "events.h"

void send_pdr_event(player_info_t *player, int ressource_number)
{
    zappy_t *my_zappy = (zappy_t *)global_zappy;
    char *response = NULL;

    new_alloc_asprintf(&response, "pdr #%d %d\n",
        player->fd, ressource_number);
    send_data(my_zappy->gui->fd, response);
}
