/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** zappy.h
*/

#pragma once

#define _GNU_SOURCE // for new_alloc_asprintf
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <regex.h>
#include <time.h>

typedef struct zappy_s zappy_t;

#include "server.h"
#include "gui.h"
#include "ia.h"
#include "log.h"
#include "init_structures.h"
#include "parsing.h"
#include "map_headers/map_generation.h"
#include "free_structures.h"
#include "game.h"
#include "garbage_collector.h"


typedef struct zappy_s {
    server_t *server;
    gui_t *gui;
    ia_t *IA;
} zappy_t;

extern const zappy_t *global_zappy;
extern bool exit_status;
