/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** send_pex_event.c
*/

#include "../../includes/gui_events/events.h"

void send_pex_event(player_info_t *player)
{
    gui_t *gui = (gui_t *)global_zappy->gui;
    char *message = NULL;

    new_alloc_asprintf(&message, "pex #%d\n", player->fd);
    send_data(gui->fd, message);
}
