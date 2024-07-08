/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** server.h
*/

#pragma once

#include "instructions_headers/instructions.h"
#include <arpa/inet.h>
#include "game.h"

typedef struct map_s map_t;
typedef struct game_s game_t;
typedef struct player_info_s player_info_t;
typedef struct client_s client_t;

typedef struct server_s {
    int fd;
    int port;

    fd_set read_fds;
    fd_set write_fds;
    int max_fd;
    struct timeval stimeout;
    double current_time;
    time_t win_time;
    double processor_time;

    struct sockaddr_in sock_ad;
    socklen_t sock_len;

    game_t *game;
    map_t *map;
    instruction_stack_t *instructions;
} server_t;

typedef struct zappy_s zappy_t;

void catch_signals(void);
void zappy_loop(zappy_t *zappy);
void server_setup(zappy_t *zappy);
// monitoring the server
void server_monitor(zappy_t *zappy);
// receive commands from GUI and IA
void server_commands(zappy_t *zappy);
// parse commands from GUI and IA
void server_stacks(zappy_t *zappy);
// send events to GUI and IA

void execute_gui_instructions(char *instruction);
void execute_ai_instructions(char *instruction, client_t *current_client,
    player_info_t *current_player);

void server_events(zappy_t *zappy);
int authentification(zappy_t *zappy, int new_socket);
void set_lowest_timeout(zappy_t *zappy);
void server_connections(zappy_t *zappy);
void exit_error(char *message);
void exit_cleanly(void);

//winning_team
bool winning_team(void);
