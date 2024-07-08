/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** server_setup
*/

#include "zappy.h"

int create_server_socket(void)
{
    int sfd;

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
        exit_error("Socket creation failed\n");
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
        exit_error("Setsockopt failed\n");
    return sfd;
}

void bind_server_socket(int fd, struct sockaddr_in *addr)
{
    int e = 0;
    socklen_t size = sizeof(struct sockaddr_in);

    e = bind(fd, (struct sockaddr *)addr, size);
    if (e < 0)
        exit_error("Bind failed\n");
}

void start_server(int fd)
{
    if (listen(fd, SOMAXCONN) < 0) {
        exit_error("Listen failed\n");
    }
}

void server_setup(zappy_t *zappy)
{
    zappy->server->fd = create_server_socket();
    bind_server_socket(zappy->server->fd, &zappy->server->sock_ad);
    start_server(zappy->server->fd);
}
