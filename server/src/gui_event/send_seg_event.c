/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** send_seg_event.c
*/

#include "../../includes/gui_events/events.h"

void send_seg_event(player_info_t *player, char *team_name)
{
    gui_t *gui = (gui_t *)global_zappy->gui;
    char *message = NULL;

    (void)player;
    new_alloc_asprintf(&message, "seg %s\n", team_name);
    send_data(gui->fd, message);
}
