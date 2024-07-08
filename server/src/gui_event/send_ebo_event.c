/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** send_ebo_event.c
*/

#include "events.h"

void send_ebo_event(player_info_t *player, int egg_nb)
{
    zappy_t *my_zappy = (zappy_t *)global_zappy;
    char *response = NULL;

    (void)player;
    new_alloc_asprintf(&response, "ebo #%d\n", egg_nb);
    send_data(my_zappy->gui->fd, response);
    log_message("log/ebo_event.log", GREEN, "ebo #%d\n", egg_nb);
}
