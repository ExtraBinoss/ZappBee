/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** execute_incantation.c
*/

#include "execute_commands.h"

static bool check_incantation(player_info_t *player, map_t *map)
{
    int nb_players_on_tile = check_number_of_players_on_tile(player);
    int nb_players_required_on_tile =
        check_player_current_level(player->level);

    log_message("log/incantation.log", RED, "nb_players_on_tile: %d |",
    nb_players_on_tile);
    log_message("log/incantation.log", RED, "nb_players_required_tile: %d\n",
    nb_players_required_on_tile);
    if (nb_players_on_tile < nb_players_required_on_tile) {
        log_message("log/incantation.log", RED, "[%d] not enough players\n",
            player->fd);
        return false;
    }
    if (check_ressources_required(player, map) == false) {
        log_message("log/incantation.log", RED, "[%d] not enough ressources\n",
            player->fd);
        return false;
    }
    return true;
}

void update_all_players_level(player_info_t *player, game_t *game)
{
    int l = player->level;

    player->level = l + 1;
    if (!game->players)
        return;
    for (player_info_t *tmp = game->players; tmp && l != 1; tmp = tmp->next) {
        if (tmp->x == player->x && tmp->y == player->y
        && (int)tmp->level == l && tmp->fd != player->fd) {
                tmp->level = l + 1;
                log_message("log/incantation.log",
                GREEN, "[%d] Player level: %ld\n", tmp->fd, tmp->level);
        }
    }
    remove_ressource_level(l, player->x, player->y);
}

void incantation(player_info_t *player)
{
    server_t *srvr = (server_t *)global_zappy->server;
    char *response = NULL;

    if (check_incantation(player, srvr->map)) {
        printf("[%d] Incantation OK %ld->%ld\n", player->fd, player->level,
            player->level + 1);
        update_all_players_level(player, srvr->game);
        send_pie_event(player, player->x, player->y, player->level);
        send_level_to_all_tiles(player, srvr->game);
        log_message("log/incantation.log", GREEN, "[%d] Incantation OK |",
        "level %ld\n", player->fd, player->level);
    } else {
        printf("[%d] Incantation KO\n", player->fd);
        new_alloc_asprintf(&response, "ko\n");
        log_message("log/incantation.log", RED, "[%d] Incantation KO %s\n",
        player->fd, response);
        send_pie_event(player, player->x, player->y, 84);
        send_data(player->fd, response);
    }
}

void freeze_players_on_tile(player_info_t *player, game_t *game, bool freeze)
{
    for (player_info_t *tmp = game->players; tmp; tmp = tmp->next) {
        if (tmp->x == player->x && tmp->y == player->y
            && tmp->level == player->level)
                tmp->is_frozen = freeze;
    }
}

void execute_incantation_command(player_info_t *player, char *arg)
{
    server_t *srvr = (server_t *)global_zappy->server;

    (void)arg;
    if (player->timer_action <= 0) {
        incantation(player);
        freeze_players_on_tile(player, srvr->game, false);
    }
}
