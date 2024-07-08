/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** authentification
*/

#include <stdio.h>
#include "zappy.h"
#include "network_headers/network_transactions.h"

static team_info_t *find_team_by_name(zappy_t *zappy, char *name)
{
    team_info_t *tmp = zappy->server->game->teams;

    if (name == NULL)
        return NULL;
    while (tmp != NULL && tmp->name != NULL) {
        if (tmp->name != NULL && strcmp(tmp->name, name) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

static int check_team_capacity(zappy_t *z, team_info_t *team, int new_socket)
{
    char data[1024] = {0};

    if (team == NULL || team->slotAvailable == 0)
        return -1;
    team->slotAvailable--;
    sprintf(data, "%d\n", team->slotAvailable);
    send_data(new_socket, data);
    memset(data, 0, 1024);
    sprintf(data, "%d %d\n", z->server->game->width, z->server->game->height);
    send_data(new_socket, data);
    return team->ID;
}

static void clean_buffer(char *buffer)
{
    for (size_t i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == '\n' || buffer[i] == '\r')
            buffer[i] = '\0';
    }
}

int send_gui_info(zappy_t *z, int new_socket)
{
    char d[1024] = {0};

    sprintf(d, "0\n%d %d\n", z->server->game->width, z->server->game->height);
    send_data(new_socket, d);
    memset(d, 0, 1024);
    return 0;
}

int authentification(zappy_t *zappy, int new_socket)
{
    char buffer[1024] = {0};
    int n = 0;
    team_info_t *team = NULL;

    send_data(new_socket, "WELCOME\n");
    n = read(new_socket, buffer, 1024);
    if (n < 0) {
        log_message("log/error_accept.log", RED, "Read failed");
        return -1;
    }
    clean_buffer(buffer);
    if (strncmp(buffer, "GRAPHIC", 7) == 0) {
        if (zappy->gui->fd == -1) {
            log_message("log/accept.log", RED, "GUI is connected");
            return send_gui_info(zappy, new_socket);
        }
        return -1;
    }
    team = find_team_by_name(zappy, buffer);
    return check_team_capacity(zappy, team, new_socket);
}
