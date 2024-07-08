/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** send_edi_event.c
*/

#include "events.h"

//new_alloc_asprintf(&data, "edi %d\n", egg->id);
//send_data(fd, data);
void send_edi_event(int fd, int egg_nb)
{
    zappy_t *my_zappy = (zappy_t *)global_zappy;
    char *response = NULL;

    (void)my_zappy;
    new_alloc_asprintf(&response, "edi #%d\n", egg_nb);
    send_data(fd, response);
}
