/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** send_pfk_event.c
*/

#include "../../includes/gui_events/events.h"

void send_pfk_event(player_info_t *player)
{
    gui_t *gui = (gui_t *)global_zappy->gui;
    char *message = NULL;

    new_alloc_asprintf(&message, "pfk %d\n", player->fd);
    send_data(gui->fd, message);
    log_message("log/gui.log", GREEN, "[Sent] pfk %d\n", player->fd);
}
