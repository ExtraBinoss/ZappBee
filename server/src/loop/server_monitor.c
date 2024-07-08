/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** server_monitor
*/

#include "zappy.h"
#include <sys/socket.h>

void monitor_overload(client_t *current_client, server_t *s)
{
    char b[1024];

    if (stack_size(current_client->stack) < 10) {
        FD_SET(current_client->fd, &s->read_fds);
        if (current_client->fd > s->max_fd) {
            s->max_fd = current_client->fd;
        }
    } else {
        printf("Client %d is overloaded\n", current_client->fd);
        while (recv(current_client->fd, b, sizeof(b), MSG_DONTWAIT) > 0)
            printf("Discarding socket content...\n");
        printf("Excess data discarded\n");
    }
}

void server_monitor(zappy_t *z)
{
    client_t *current_client = z->IA->clients;
    server_t *s = z->server;
    int i = 0;

    s->max_fd = s->fd;
    if (z->gui->fd > s->max_fd) {
        s->max_fd = z->gui->fd;
    }
    FD_ZERO(&s->read_fds);
    FD_SET(s->fd, &s->read_fds);
    FD_SET(z->gui->fd, &s->read_fds);
    while (current_client != NULL) {
        monitor_overload(current_client, s);
        current_client = current_client->next;
    }
    i = select(s->max_fd + 1, &s->read_fds, NULL, NULL, &z->server->stimeout);
    if (i < 0) {
        exit_error("Select failed\n");
    }
}
