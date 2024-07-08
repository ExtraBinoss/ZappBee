/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** send_pic_event.c
*/

#include "../../includes/gui_events/events.h"

//start of an incantation (by the first player)
void send_pic_event(int args[3], char *player_fds)
{
    int x = args[0];
    int y = args[1];
    int level = args[2];
    va_list players;
    zappy_t *my_zappy = (zappy_t *)global_zappy;
    char *response = NULL;

    va_end(players);
    new_alloc_asprintf(&response, "pic %d %d %d %s\n",
        x, y, level, player_fds);
    send_data(my_zappy->gui->fd, response);
    log_message("log/incantation.log", GREEN, "pic %d %d %d %s\n",
        x, y, level, player_fds);
}
