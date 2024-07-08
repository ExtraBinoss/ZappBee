/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** gui.h
*/

#pragma once

#include <netinet/in.h>
#include "network_headers/network_stack.h"

typedef struct gui_s {
    struct sockaddr_in addr;
    int fd;
    network_stack_t *stack;
} gui_t;
