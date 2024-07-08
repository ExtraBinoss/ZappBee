/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** free_structures.h
*/

#pragma once

#include "zappy.h"

typedef struct zappy_s zappy_t;
typedef struct server_s server_t;
typedef struct gui_s gui_t;
typedef struct ia_s ia_t;
typedef struct map_s map_t;
typedef struct game_s game_t;

void free_map(map_t *map);
void free_game(game_t *game);
