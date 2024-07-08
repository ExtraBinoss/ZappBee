/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** set_timer_instructions_bis.c
*/

#include "set_timer_instructions.h"

void set_fork_timer(player_info_t *player, char *arg)
{
    (void)arg;
    if (player->timer_action == 0) {
        player->timer_action = 42 / global_zappy->server->game->freq;
        player->elapsed_time = 0;
        player->lastT = 0;
        player->exec_command->command = new_alloc_str("Fork");
        player->exec_command->arg = NULL;
    }
}

void set_inventory_timer(player_info_t *player, char *arg)
{
    (void)arg;
    if (player->timer_action == 0) {
        player->timer_action = 1 / global_zappy->server->game->freq;
        player->elapsed_time = 0;
        player->lastT = 0;
        player->exec_command->command = new_alloc_str("Inventory");
        player->exec_command->arg = NULL;
    }
}

void set_look_timer(player_info_t *player, char *arg)
{
    (void)arg;
    if (player->timer_action == 0) {
        player->timer_action = 7 / global_zappy->server->game->freq;
        player->elapsed_time = 0;
        player->lastT = 0;
        player->exec_command->command = new_alloc_str("Look");
        player->exec_command->arg = NULL;
    }
}

void set_set_object_timer(player_info_t *player, char *arg)
{
    if (player->timer_action == 0) {
        player->timer_action = 7 / global_zappy->server->game->freq;
        player->elapsed_time = 0;
        player->lastT = 0;
        player->exec_command->command = new_alloc_str("Set");
        player->exec_command->arg = new_alloc_str(arg);
    }
}

void set_take_object_timer(player_info_t *player, char *arg)
{
    if (player->timer_action == 0) {
        player->timer_action = 7 / global_zappy->server->game->freq;
        player->elapsed_time = 0;
        player->lastT = 0;
        player->exec_command->command = new_alloc_str("Take");
        if (arg != NULL) {
            player->exec_command->arg = new_alloc_str(arg);
        }
    }
}
