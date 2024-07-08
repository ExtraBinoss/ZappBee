/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** server_commands
*/

#include "zappy.h"
#include "network_transactions.h"

void remove_client_soft(client_t **clients, client_t *client)
{
    client_t *tmp = *clients;

    if (tmp == client) {
        *clients = tmp->next;
        remove_from_garbage(tmp);
        return;
    }
    while (tmp->next != NULL) {
        if (tmp->next == client) {
            tmp->next = client->next;
            remove_from_garbage(client->stack);
            remove_from_garbage(client);
            return;
        }
        tmp = tmp->next;
    }
}

void server_commands(zappy_t *zappy)
{
    client_t *client = zappy->IA->clients;
    client_t *next_client = NULL;
    bool status = true;

    while (client != NULL) {
        next_client = client->next;
        if (FD_ISSET(client->fd, &zappy->server->read_fds))
            status = receive_data(client->fd, &client->stack);
        if (status == false)
            remove_client_soft(&zappy->IA->clients, client);
        client = next_client;
    }
    if (FD_ISSET(zappy->gui->fd, &zappy->server->read_fds)) {
        status = receive_data(zappy->gui->fd, &zappy->gui->stack);
        if (status == false) {
            close(zappy->gui->fd);
            zappy->gui->fd = -1;
            remove_from_garbage(zappy->gui->stack);
        }
    }
}
