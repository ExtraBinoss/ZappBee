/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** execute_instructions_commands.h
*/

#pragma once

#include "game.h"
#include "network_transactions.h"
#include "linked_list_utils.h"
#include "garbage_collector.h"

typedef struct player_info_s player_info_t;
typedef struct zappy_s zappy_t;
typedef struct game_s game_t;

void execute_msz_command(player_info_t *player, char *instruction);
void execute_bct_command(player_info_t *player, char *instruction);
void execute_mct_command(player_info_t *player, char *instruction);
void execute_tna_command(player_info_t *player, char *instruction);
void execute_ppo_command(player_info_t *player, char *instruction);
void execute_plv_command(player_info_t *player, char *instruction);
void execute_pin_command(player_info_t *player, char *instruction);
void execute_sgt_command(player_info_t *player, char *instruction);
void execute_sst_command(player_info_t *player, char *instruction);
