/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** incantation_utils.c
*/

#include "execute_commands.h"
#include "execute_instructions_commands.h"

static void remove_used_ressources_2(tile_t *tile,
    unsigned long resources_to_remove[6])
{
    map_t *map = (map_t *)global_zappy->server->map;

    if (resources_to_remove[3] > 0
    && tile->tile_ressources->mendiane >= resources_to_remove[3]) {
        tile->tile_ressources->mendiane -= resources_to_remove[3];
        map->ressources_left->mendiane -= resources_to_remove[3];
    }
    if (resources_to_remove[4] > 0
    && tile->tile_ressources->phiras >= resources_to_remove[4]) {
        tile->tile_ressources->phiras -= resources_to_remove[4];
        map->ressources_left->phiras -= resources_to_remove[4];
    }
    if (resources_to_remove[5] > 0
    && tile->tile_ressources->thystame >= resources_to_remove[5]) {
        tile->tile_ressources->thystame -= resources_to_remove[5];
        map->ressources_left->thystame -= resources_to_remove[5];
    }
}

//to change with the ressources left too
void remove_used_resources(tile_t *tile, unsigned long resources_to_remove[6])
{
    map_t *map = (map_t *)global_zappy->server->map;

    if (resources_to_remove[0] > 0
    && tile->tile_ressources->linemate >= resources_to_remove[0]) {
        tile->tile_ressources->linemate -= resources_to_remove[0];
        map->ressources_left->linemate -= resources_to_remove[0];
    }
    if (resources_to_remove[1] > 0
    && tile->tile_ressources->deraumere >= resources_to_remove[1]) {
        tile->tile_ressources->deraumere -= resources_to_remove[1];
        map->ressources_left->deraumere -= resources_to_remove[1];
    }
    if (resources_to_remove[2] > 0
    && tile->tile_ressources->sibur >= resources_to_remove[2]) {
        tile->tile_ressources->sibur -= resources_to_remove[2];
        map->ressources_left->sibur -= resources_to_remove[2];
    }
    remove_used_ressources_2(tile, resources_to_remove);
}

static bool check_ressources_required_3(player_info_t *player,
    tile_t *tile)
{
    if (player->level == 6 && tile->tile_ressources->linemate >= 1 &&
        tile->tile_ressources->deraumere >= 2 &&
        tile->tile_ressources->sibur >= 3 &&
        tile->tile_ressources->phiras >= 1) {
            return true;
        }
    if (player->level == 7 && tile->tile_ressources->linemate >= 2 &&
        tile->tile_ressources->deraumere >= 2 &&
        tile->tile_ressources->sibur >= 2 &&
        tile->tile_ressources->mendiane >= 2 &&
        tile->tile_ressources->phiras >= 2 &&
        tile->tile_ressources->thystame >= 1) {
            return true;
        }
    return false;
}

static bool check_ressources_required_2(player_info_t *player,
    tile_t *tile)
{
    if (player->level == 5 && tile->tile_ressources->linemate >= 1 &&
        tile->tile_ressources->deraumere >= 2 &&
        tile->tile_ressources->sibur >= 1 &&
        tile->tile_ressources->mendiane >= 3) {
            return true;
        }
    return false;
}

static bool check_ressources_required_1(player_info_t *player, tile_t *tile)
{
    if (player->level == 3 && tile->tile_ressources->linemate >= 2 &&
        tile->tile_ressources->sibur >= 1 &&
        tile->tile_ressources->phiras >= 2) {
            return true;
        }
    if (player->level == 4 && tile->tile_ressources->linemate >= 1 &&
        tile->tile_ressources->deraumere >= 1 &&
        tile->tile_ressources->sibur >= 2 &&
        tile->tile_ressources->phiras >= 1) {
            return true;
        }
    return false;
}

bool check_ressources_required(player_info_t *player, map_t *map)
{
    tile_t *tile = find_tile_by_pos(map->tiles, player->x, player->y);

    if (player->level == 1 && tile->tile_ressources->linemate >= 1) {
        return true;
    }
    if (player->level == 2 && tile->tile_ressources->linemate >= 1 &&
        tile->tile_ressources->deraumere >= 1 &&
        tile->tile_ressources->sibur >= 1) {
            return true;
        }
    if (check_ressources_required_1(player, tile))
        return true;
    if (check_ressources_required_2(player, tile))
        return true;
    if (check_ressources_required_3(player, tile))
        return true;
    return false;
}

static char *append_player_fd(char *player_fds, char *tmp)
{
    if (player_fds) {
        player_fds = new_realloc_str(player_fds,
            strlen(player_fds) + strlen(tmp) + 2);
        strcat(player_fds, " ");
    } else {
        player_fds = new_alloc(strlen(tmp) + 1);
        player_fds[0] = '\0';
    }
    strcat(player_fds, tmp);
    return player_fds;
}

char *get_player_fds_on_tile(player_info_t *player)
{
    game_t *game = (game_t *)global_zappy->server->game;
    char *player_fds = NULL;
    char *tmp = NULL;

    if (!game->players)
        return NULL;
    for (player_info_t *tmp_player = game->players; tmp_player;
        tmp_player = tmp_player->next) {
        if (tmp_player->x == player->x && tmp_player->y == player->y
            && tmp_player->level == player->level) {
            new_alloc_asprintf(&tmp, "#%d", tmp_player->fd);
            player_fds = append_player_fd(player_fds, tmp);
        }
    }
    log_message("log/incantation.log", RED, "player_fds: [%s]\n", player_fds);
    return player_fds;
}

static void remove_used_resources_level(tile_t *tile, int incantation_level)
{
    if (incantation_level == 1)
        remove_used_resources(tile, (unsigned long[6]) {1, 0, 0, 0, 0, 0});
    if (incantation_level == 2)
        remove_used_resources(tile, (unsigned long[6]) {1, 1, 1, 0, 0, 0});
    if (incantation_level == 3)
        remove_used_resources(tile, (unsigned long[6]) {2, 0, 1, 0, 2, 0});
    if (incantation_level == 4)
        remove_used_resources(tile, (unsigned long[6]) {1, 1, 2, 0, 1, 0});
    if (incantation_level == 5)
        remove_used_resources(tile, (unsigned long[6]) {1, 2, 1, 3, 0, 0});
    if (incantation_level == 6)
        remove_used_resources(tile, (unsigned long[6]) {1, 2, 3, 0, 1, 0});
    if (incantation_level == 7)
        remove_used_resources(tile, (unsigned long[6]) {2, 2, 2, 2, 2, 1});
}

void remove_ressource_level(int level, int pos_x, int pos_y)
{
    tile_t *tile = (tile_t *)global_zappy->server->map->tiles;
    tile_t *current_tile = find_tile_by_pos(tile, pos_x, pos_y);
    char *message = NULL;

    remove_used_resources_level(current_tile, level);
    new_alloc_asprintf(&message, "bct %d %d\n", pos_x, pos_y);
    execute_bct_command(NULL, message);
}
