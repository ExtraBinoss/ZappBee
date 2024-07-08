/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** search_player.c
*/

#include "linked_list_utils.h"
#include "map_generation.h"

player_info_t *search_player_by_team_name(player_info_t *head,
    const char *team_name)
{
    player_info_t *current_player = head;

    while (current_player != NULL) {
        if (current_player->team_name == NULL) {
            current_player = current_player->next;
            continue;
        }
        if (strcmp(current_player->team_name, team_name) == 0) {
            return current_player;
        }
        current_player = current_player->next;
    }
    return NULL;
}

team_info_t *find_team_by_name(team_info_t *head, const char *team_name)
{
    team_info_t *current_team = head;

    while (current_team != NULL) {
        if (current_team->name == NULL) {
            current_team = current_team->next;
            continue;
        }
        if (strcmp(current_team->name, team_name) == 0) {
            return current_team;
        }
        current_team = current_team->next;
    }
    return NULL;
}

tile_t *find_tile_by_pos(tile_t *head, int x, int y)
{
    tile_t *current_tile = head;

    while (current_tile != NULL) {
        if ((int)current_tile->x == x && (int)current_tile->y == y) {
            return current_tile;
        }
        current_tile = current_tile->next;
    }
    return NULL;
}

player_info_t *find_player_by_pos(player_info_t *head, int x, int y)
{
    player_info_t *current_player = head;

    while (current_player != NULL) {
        if (current_player->x == x && current_player->y == y) {
            return current_player;
        }
        current_player = current_player->next;
    }
    return NULL;
}

player_info_t *find_player_by_fd(player_info_t *players, int fd)
{
    player_info_t *player = NULL;

    for (player = players; player; player = player->next) {
        if (player->fd == fd) {
            return (player);
        }
    }
    return (NULL);
}
