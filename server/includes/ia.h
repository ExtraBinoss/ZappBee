/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** ia.h
*/

#pragma once

#include <netinet/in.h>
#include "network_headers/network_stack.h"

typedef struct client_s client_t;

typedef struct client_s {
    // client connection informations
    struct sockaddr_in addr;
    // client file descriptor
    int fd;

    // client commands stack
    network_stack_t *stack;

    // linked list
    client_t *next;
} client_t;

typedef struct ia_s {
    //linked list of clients
    client_t *clients;
} ia_t;
