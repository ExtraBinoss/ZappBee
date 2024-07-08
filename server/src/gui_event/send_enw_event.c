/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** send_enw_event.c
*/

#include "events.h"

/*new_alloc_asprintf(&data, "enw #%d #%d %d %d\n",
egg->id, player->fd, egg->x, egg->y);
send_data(myzappy->gui->fd, data);
*/
void send_enw_event(int egg_nb, int player_fd, int x, int y)
{
    zappy_t *my_zappy = (zappy_t *)global_zappy;
    char *response = NULL;

    new_alloc_asprintf(&response, "enw #%d #%d %d %d\n",
        egg_nb, player_fd, x, y);
    send_data(my_zappy->gui->fd, response);
}
