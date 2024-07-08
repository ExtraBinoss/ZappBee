/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** linked_list.h
*/

#pragma once

#include "game.h"

typedef struct player_info_s player_info_t;

player_info_t *search_player_by_team_name(player_info_t *head,
    const char *team_name);
team_info_t *find_team_by_name(team_info_t *head, const char *team_name);
tile_t *find_tile_by_pos(tile_t *head, int x, int y);
player_info_t *find_player_by_pos(player_info_t *head, int x, int y);
size_t find_object_quantity_by_name(tile_t *tile, const char *object_name);
size_t find_object_quantity_player_inventory(player_info_t *player,
    const char *object_name);
player_info_t *find_player_by_fd(player_info_t *players, int fd);
