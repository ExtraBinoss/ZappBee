/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** incantation_utils_bis.c
*/

#include "execute_commands.h"
#include "execute_instructions_commands.h"

void send_level_to_all_tiles(player_info_t *p, game_t *g)
{
    char *response = NULL;

    new_alloc_asprintf(&response, "Current level: %ld\n", p->level);
    send_data(p->fd, response);
    remove_from_garbage(response);
    new_alloc_asprintf(&response, "plv #%d\n", p->fd);
    execute_plv_command(p, response);
    remove_from_garbage(response);
    for (player_info_t *t = g->players; t && p->level != 2; t = t->next) {
        if (t->x == p->x && t->y == p->y
            && t->level == p->level && t->fd != p->fd) {
            new_alloc_asprintf(&response, "Current level: %ld\n", p->level);
            send_data(t->fd, response);
            remove_from_garbage(response);
            new_alloc_asprintf(&response, "plv #%d\n", p->fd);
            execute_plv_command(t, response);
            remove_from_garbage(response);
        }
    }
}

int check_player_current_level(int level)
{
    if (level == 1)
        return 1;
    if (level == 2)
        return 2;
    if (level == 3)
        return 2;
    if (level == 4)
        return 4;
    if (level == 5)
        return 4;
    if (level == 6)
        return 6;
    if (level == 7)
        return 6;
    return 0;
}

int check_number_of_players_on_tile(player_info_t *player)
{
    game_t *game = (game_t *)global_zappy->server->game;
    int nb_players = 0;

    if (!game->players)
        return 0;
    for (player_info_t *tmp = game->players; tmp; tmp = tmp->next) {
        if (tmp->x == player->x && tmp->y == player->y)
            nb_players++;
    }
    return nb_players;
}
