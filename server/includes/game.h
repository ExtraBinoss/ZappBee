/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** game.h
*/

#pragma once

#include "zappy.h"

typedef struct zappy_s zappy_t;

typedef struct team_egg_s {
    size_t x;
    size_t y;

    int id;
    struct team_egg_s *next;
} team_egg_t;

typedef struct team_info_s {
    char *name;
    int slotAvailable;
    int slotMax;
    int ID;
    int spawnpoint_x;
    int spawnpoint_y;
    team_egg_t *eggs;

    struct team_info_s *next;
} team_info_t;

typedef struct player_inventory_s {
    size_t food;
    size_t linemate;
    size_t deraumere;
    size_t sibur;
    size_t mendiane;
    size_t phiras;
    size_t thystame;
} player_inventory_t;

typedef enum player_direction_e {
    UP,
    RIGHT,
    DOWN,
    LEFT
} player_direction_t;

typedef struct exec_command_s {
    char *command;
    char *arg;
} exec_command_t;

//player info
typedef struct player_info_s {
    char *team_name;

    int x;
    int y;
    size_t level;
    int fd;
    int team_id;
    player_inventory_t *inventory;
    player_direction_t direction;
    exec_command_t *exec_command;

    int clock;
    int lastT;
    double elapsed_time;

    double timer_action;
    double timer_death;
    bool is_alive;
    bool is_frozen;
    struct player_info_s *next;
} player_info_t;

typedef struct game_s {
    int clientsNb; // number of authorized clients per team
    int width; // width of the world
    int height; // height of the world
    double freq; // reciprocal of time unit for execution of actions
    int egg_max_id; // highest egg id
    int team_max_id; // highest team id
    double timer_regen; // time until resources regenerate
    team_info_t *teams; // list of teams (linked_list)
    player_info_t *players; // list of players (linked_list)
} game_t;

void decrement_game_timers(zappy_t *zappy, double time_elapsed);
int set_player_spawnpoint(player_info_t *player, team_info_t *team);
void set_teams_spawnpoints(zappy_t *zappy);
