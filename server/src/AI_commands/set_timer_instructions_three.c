/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** set_timer_instructions_three.c
*/

#include "set_timer_instructions.h"

void set_forward_timer(player_info_t *player, char *arg)
{
    (void)arg;
    if (player->timer_action == 0) {
        player->timer_action = 7 / global_zappy->server->game->freq;
        player->elapsed_time = 0;
        player->lastT = 0;
        player->exec_command->command = new_alloc_str("Forward");
        player->exec_command->arg = NULL;
    }
}

void set_right_timer(player_info_t *player, char *arg)
{
    (void)arg;
    if (player->timer_action == 0) {
        player->timer_action = 7 / global_zappy->server->game->freq;
        player->elapsed_time = 0;
        player->lastT = 0;
        player->exec_command->command = new_alloc_str("Right");
        player->exec_command->arg = NULL;
    }
}

void set_left_timer(player_info_t *player, char *arg)
{
    (void)arg;
    if (player->timer_action == 0) {
        player->timer_action = 7 / global_zappy->server->game->freq;
        player->elapsed_time = 0;
        player->lastT = 0;
        player->exec_command->command = new_alloc_str("Left");
        player->exec_command->arg = NULL;
    }
}
