/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** send_pie_event.c
*/

#include "../../includes/gui_events/events.h"

void send_pie_event(player_info_t *player, int x, int y, int result)
{
    gui_t *gui = (gui_t *)global_zappy->gui;
    char *message = NULL;

    (void)player;
    new_alloc_asprintf(&message, "pie %d %d %d\n", x, y, result);
    send_data(gui->fd, message);
    remove_from_garbage(message);
}
