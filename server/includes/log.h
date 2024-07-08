/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** log.h
*/

#pragma once

#include <stdio.h>
#include <stdarg.h>

#include "zappy.h"

typedef struct zappy_s zappy_t;
typedef struct map_s map_t;
typedef struct game_s game_t;

typedef enum color_s {
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    RESET
} color_t;

void log_message(const char *filename, color_t color, const char *format, ...);
void argument_logs(void);
void regenerate_map_logs(game_t *game, map_t *map);
