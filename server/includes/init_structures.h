/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** init_structures.h
*/

#pragma once

#include "zappy.h"

typedef struct zappy_s zappy_t;
typedef struct team_info_s team_info_t;
typedef struct server_s server_t;

team_info_t *init_team_struct(void);
void init_server_struct(zappy_t *zappy);
void init_gui_struct(zappy_t *zappy);
void init_ia_struct(zappy_t *zappy);
void init_all_struct(zappy_t *zappy);
