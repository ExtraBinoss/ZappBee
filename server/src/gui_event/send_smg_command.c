/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** send_smg_command.c
*/

#include "../../includes/gui_events/events.h"

void send_smg_event(player_info_t *player, char *cmd)
{
    zappy_t *my_zappy = (zappy_t *)global_zappy;
    char *response = NULL;

    (void)player;
    new_alloc_asprintf(&response, "smg %s\n", cmd);
    send_data(my_zappy->gui->fd, response);
}
