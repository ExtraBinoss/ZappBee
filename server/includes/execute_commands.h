/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** execute_commands.h
*/

#pragma once

#include "game.h"
#include "linked_list_utils.h"
#include "network_transactions.h"
#include "events.h"

typedef struct look_string_s {
    char *data;
} look_string_t;

typedef struct game_s game_t;
typedef struct player_info_s player_info_t;

typedef struct set_timer_instruction_s {
    char *instruction;
    void (*set_timer)(player_info_t *player, char *arg);
} set_timer_instruction_t;

void set_timer_instruction(player_info_t *player, char *command);
void handle_instructions(zappy_t *zappy, player_info_t *player);
void decrement_real_player_timers(zappy_t *zappy, double elapsed);
void update_player_state(player_info_t *player);

void execute_forward_command(player_info_t *player, char *arg);
void execute_turn_right_command(player_info_t *player, char *arg);
void execute_turn_left_command(player_info_t *player, char *arg);
void execute_look_command(player_info_t *player, char *arg);
void execute_inventory_command(player_info_t *player, char *arg);
void execute_broadcast_command(player_info_t *player, char *arg);
void execute_connect_nbr_command(player_info_t *player, char *arg);
void execute_eject_command(player_info_t *player, char *arg);
void execute_fork_command(player_info_t *player, char *arg);
void execute_incantation_command(player_info_t *player, char *arg);
void execute_set_object_command(player_info_t *player, char *arg);
void execute_take_object_command(player_info_t *player, char *arg);

void freeze_players_on_tile(player_info_t *player, game_t *game, bool freeze);
void remove_used_resources(tile_t *tile, unsigned long resources_to_remove[6]);
bool check_ressources_required(player_info_t *player, map_t *map);
void append_to_look_string(look_string_t *buffer, const char *data);
bool any_space_needed(tile_t *tile);
void append_resource(look_string_t *buffer, const char *resource,
    int *object_found);
bool space_needed(size_t ressource);
void append_player_to_buffer(player_info_t *current_player, tile_t *tile,
    look_string_t *buffer, int *player_found);
char *remove_special_chars(char *input);
void remove_tile_ressource_and_map_ressource(tile_t *tile,
    char *object_name);
void add_tile_ressource_and_map_ressource(tile_t *tile,
    char *object_name);
void log_take_object(player_info_t *player, char *object_name,
    size_t number_of_object);
char *get_player_fds_on_tile(player_info_t *player);
void remove_ressource_level(int level, int pos_x, int pos_y);
void send_level_to_all_tiles(player_info_t *player, game_t *game);
int check_player_current_level(int level);
int check_number_of_players_on_tile(player_info_t *player);
void send_ok_take(player_info_t *player, int ressource_enum);
void send_ok_set(player_info_t *player, int ressource_enum);
