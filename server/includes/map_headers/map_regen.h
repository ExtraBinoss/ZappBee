/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** map_regen.h
*/

#pragma once

#include "server.h"

#define MIN(a, b) ((a < b) ? a : b)

typedef struct server_s server_t;
typedef struct zappy_s zappy_t;

void update_and_regenerate_map(zappy_t *zappy);
