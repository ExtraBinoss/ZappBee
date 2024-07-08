/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** free_structures.c
*/

#include "zappy.h"

static void free_rest_of_map(map_t *map)
{
    if (map->ressources_max != NULL)
        free(map->ressources_max);
    if (map->ressources_left != NULL)
        free(map->ressources_left);
    if (map->missing_ressources != NULL)
        free(map->missing_ressources);
}

void free_map(map_t *map)
{
    tile_t *tile = map->tiles;
    tile_t *tmp = NULL;

    while (tile != NULL) {
        tmp = tile;
        if (tile->tile_ressources != NULL)
            free(tile->tile_ressources);
        tile = tile->next;
        free(tmp);
    }
    printf("freeing map\n");
    free_rest_of_map(map);
    if (map != NULL)
        free(map);
}

static void free_players(game_t *game)
{
    player_info_t *current_player = game->players;
    player_info_t *next_player = NULL;

    while (current_player != NULL) {
        next_player = current_player->next;
        free(current_player->team_name);
        free(current_player->inventory);
        free(current_player->exec_command);
        free(current_player);
        current_player = next_player;
    }
}

void free_game(game_t *game)
{
    team_info_t *current_team = game->teams;
    team_info_t *next_team;

    while (current_team != NULL) {
        next_team = current_team->next;
        free(current_team->name);
        free(current_team->eggs);
        free(current_team);
        current_team = next_team;
    }
    free_players(game);
    free(game);
}
