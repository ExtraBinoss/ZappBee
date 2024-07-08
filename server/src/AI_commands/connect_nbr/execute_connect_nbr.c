/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** execute_connectNbr.c
*/

#include "execute_commands.h"

static void print_slot_available(player_info_t *player, team_info_t *team)
{
    char *msg = NULL;
    int slot_available = team->slotAvailable;

    if (slot_available > 0) {
        new_alloc_asprintf(&msg, "%d\n", slot_available);
        send_data(player->fd, msg);
        log_message("log/ai_commands.log", GREEN, "[%d] Connect_nbr OK : %d\n",
            player->fd, slot_available);
    } else {
        send_data(player->fd, "0\n");
    }
}

void execute_connect_nbr_command(player_info_t *player, char *arg)
{
    zappy_t *myzappy = (zappy_t *)global_zappy;
    team_info_t *team = NULL;

    (void)arg;
    team = find_team_by_name(myzappy->server->game->teams, player->team_name);
    if (team == NULL)
        return;
    print_slot_available(player, team);
    printf("[%d] Slots available: %d\n", player->fd, team->slotAvailable);
    log_message("log/ai_commands.log", GREEN, "[%d] Connect_nbr OK\n",
        player->fd);
}
