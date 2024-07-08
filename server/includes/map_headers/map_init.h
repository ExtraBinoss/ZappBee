/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** map_init.h
*/

#pragma once

#include "map_generation.h"

typedef struct tile_s tile_t;

void setup_map(void);
void init_tiles(tile_t *tile, int tile_id, size_t x, size_t y);
