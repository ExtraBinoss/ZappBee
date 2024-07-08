/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** connection_spawnpoint
*/

#include "zappy.h"
#include "network_headers/network_transactions.h"
#include "events.h"

int set_player_spawnpoint(player_info_t *player, team_info_t *team)
{
    zappy_t *my_zappy = (zappy_t *) global_zappy;
    team_egg_t *tmp = NULL;

    if (team->eggs != NULL) {
        player->x = team->eggs->x;
        player->y = team->eggs->y;
        tmp = team->eggs;
        team->eggs = team->eggs->next;
        if (my_zappy->gui->fd != -1) {
            send_ebo_event(player, tmp->id);
        }
        remove_from_garbage(tmp);
        return 1;
    }
    player->x = team->spawnpoint_x;
    player->y = team->spawnpoint_y;
    return 0;
}
