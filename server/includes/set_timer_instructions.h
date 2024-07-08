/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** set_timer_instructions.h
*/

#pragma once

#include "zappy.h"

typedef struct player_info_s player_info_t;
typedef struct server_s server_t;

//setters timer and struct exec_commands from the player
void set_incantation_timer(player_info_t *player, char *arg);
void set_broadcast_timer(player_info_t *player, char *arg);
void set_connect_nbr_timer(player_info_t *player, char *arg);
void set_direction_timer(player_info_t *player, char *arg);
void set_eject_timer(player_info_t *player, char *arg);
void set_fork_timer(player_info_t *player, char *arg);
void set_forward_timer(player_info_t *player, char *arg);
void set_inventory_timer(player_info_t *player, char *arg);
void set_look_timer(player_info_t *player, char *arg);
void set_set_object_timer(player_info_t *player, char *arg);
void set_take_object_timer(player_info_t *player, char *arg);
void set_left_timer(player_info_t *player, char *arg);
void set_right_timer(player_info_t *player, char *arg);
