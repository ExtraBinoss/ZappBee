/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** events.h
*/

#pragma once

#define _GNU_SOURCE // for new_alloc_asprintf
#include "network_transactions.h"
#include "game.h"
#include "zappy.h"
#include <stdarg.h>

void send_pdr_event(player_info_t *player, int ressource_number);
void send_pgt_event(player_info_t *player, int ressource_number);
void send_pbc_event(player_info_t *player, char *cmd);
void send_pnw_event(player_info_t *player);
void send_pdi_event(player_info_t *player);
void send_seg_event(player_info_t *player, char *team_name);
void send_smg_event(player_info_t *player, char *cmd);
void send_pfk_event(player_info_t *player);
void send_ebo_event(player_info_t *player, int egg_nb);
void send_enw_event(int egg_nb, int player_fd, int x, int y);
void send_edi_event(int fd, int egg_nb);
void send_pex_event(player_info_t *player);
void send_pie_event(player_info_t *player, int x, int y, int result);
void send_pic_event(int args[3], char *player_fds);
