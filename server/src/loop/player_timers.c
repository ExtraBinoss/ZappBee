/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** player_timers
*/

#include "zappy.h"
#include "execute_commands.h"

void handle_player_timer(player_info_t *player, zappy_t *zappy, double elapsed)
{
    if (player->timer_action > 0) {
        player->timer_action -= elapsed;
        if (player->timer_action <= 0) {
            player->timer_action = 0;
            handle_instructions(zappy, player);
        }
    }
}

void decrement_real_player_timers(zappy_t *zappy, double elapsed)
{
    player_info_t *p = zappy->server->game->players;

    while (p != NULL) {
        handle_player_timer(p, zappy, elapsed);
        p = p->next;
    }
}

void set_lowest_timeout(zappy_t *z)
{
    player_info_t *player = z->server->game->players;
    double lo = 20;

    while (player != NULL) {
        if (player->is_alive == false) {
            player = player->next;
            continue;
        }
        if (player->timer_action < lo && player->timer_action >= 0.0001)
            lo = player->timer_action;
        if (player->timer_death < lo && player->timer_death >= 0.0001)
            lo = player->timer_death;
        player = player->next;
    }
    if (lo > z->server->game->timer_regen
        && z->server->game->timer_regen > 0.0001)
        lo = z->server->game->timer_regen;
    z->server->stimeout.tv_sec = (int) lo;
    z->server->stimeout.tv_usec = (lo - z->server->stimeout.tv_sec) * 1e6;
}

void decrement_game_timers(zappy_t *zappy, double time_elapsed)
{
    player_info_t *player = zappy->server->game->players;

    while (player) {
        if (player->timer_death > 0 && player->is_alive != false) {
            player->timer_death -= time_elapsed;
        }
        if (player->timer_death <= 0 && player->is_alive != false) {
            printf("[%d] FOOD -1, current food = %ld\n", player->fd,
                player->inventory->food);
            update_player_state(player);
        }
        player = player->next;
    }
    zappy->server->game->timer_regen -= time_elapsed;
    if (zappy->server->game->timer_regen <= 0)
        zappy->server->game->timer_regen = 0;
}
