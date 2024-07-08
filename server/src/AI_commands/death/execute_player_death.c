/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** execute_player_death.c
*/

#include "execute_commands.h"

static void handle_player_death(player_info_t *player)
{
    team_info_t *team = find_team_by_name(global_zappy->server->game->teams,
        player->team_name);

    if (team == NULL)
        return;
    team->slotAvailable += 1;
    send_pdi_event(player);
    player->is_alive = false;
    send_data(player->fd, "dead\n");
}

void update_player_state(player_info_t *player)
{
    if (player->inventory->food <= 0 && player->timer_death <= 0) {
        printf("Player %d is dead\n", player->fd);
        handle_player_death(player);
        log_message("log/death.log", RED, "[%d] Player death OK, food: %d\n",
            player->fd, player->inventory->food);
    }
    if (player->timer_death <= 0) {
        player->timer_death = 126 / global_zappy->server->game->freq;
        log_message("log/death.log", GREEN, "player still has food %d\n",
            player->inventory->food);
        player->inventory->food -= 1;
    }
}
