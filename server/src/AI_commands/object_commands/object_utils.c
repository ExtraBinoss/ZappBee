/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** object_utils.c
*/

#include "execute_commands.h"

char *remove_special_chars(char *input)
{
    int length = strlen(input);
    char *result = new_alloc(length + 1);
    int i = 0;
    int j = 0;

    for (i = 0; i < length; i++) {
        if (input[i] != ' ' && input[i] != '\n'
            && input[i] != '\r' && input[i] != '\t') {
                result[j] = input[i];
                j += 1;
        }
    }
    result[j] = '\0';
    return result;
}

static void remove_tile_ressource_and_map_ressource_2(tile_t *tile,
    char *object_name, map_t *map)
{
    if (strcasecmp(object_name, "mendiane") == 0) {
        tile->tile_ressources->mendiane -= 1;
        map->ressources_left->mendiane -= 1;
        return;
    }
    if (strcasecmp(object_name, "phiras") == 0) {
        tile->tile_ressources->phiras -= 1;
        map->ressources_left->phiras -= 1;
        return;
    }
    if (strcasecmp(object_name, "thystame") == 0) {
        tile->tile_ressources->thystame -= 1;
        map->ressources_left->thystame -= 1;
        return;
    }
}

void remove_tile_ressource_and_map_ressource(tile_t *tile,
    char *object_name)
{
    map_t *map = (map_t *)global_zappy->server->map;

    log_message("log/ai_commands.log", GREEN, "RM %s tile\n", object_name);
    if (strcasecmp(object_name, "food") == 0) {
        tile->tile_ressources->food -= 1;
        map->ressources_left->food -= 1;
    }
    if (strcasecmp(object_name, "linemate") == 0) {
        tile->tile_ressources->linemate -= 1;
        map->ressources_left->linemate -= 1;
    }
    if (strcasecmp(object_name, "deraumere") == 0) {
        tile->tile_ressources->deraumere -= 1;
        map->ressources_left->deraumere -= 1;
    }
    if (strcasecmp(object_name, "sibur") == 0) {
        tile->tile_ressources->sibur -= 1;
        map->ressources_left->sibur -= 1;
    }
    remove_tile_ressource_and_map_ressource_2(tile, object_name, map);
}

void add_tile_ressource_and_map_ressource_2(tile_t *tile,
    char *object_name, map_t *map)
{
    if (strcasecmp(object_name, "mendiane") == 0) {
        tile->tile_ressources->mendiane += 1;
        map->ressources_left->mendiane += 1;
    }
    if (strcasecmp(object_name, "phiras") == 0) {
        tile->tile_ressources->phiras += 1;
        map->ressources_left->phiras += 1;
    }
    if (strcasecmp(object_name, "thystame") == 0) {
        tile->tile_ressources->thystame += 1;
        map->ressources_left->thystame += 1;
    }
}

void add_tile_ressource_and_map_ressource(tile_t *tile,
    char *object_name)
{
    map_t *map = (map_t *)global_zappy->server->map;

    if (strcasecmp(object_name, "food") == 0) {
        tile->tile_ressources->food += 1;
        map->ressources_left->food += 1;
    }
    if (strcasecmp(object_name, "linemate") == 0) {
        tile->tile_ressources->linemate += 1;
        map->ressources_left->linemate += 1;
    }
    if (strcasecmp(object_name, "deraumere") == 0) {
        tile->tile_ressources->deraumere += 1;
        map->ressources_left->deraumere += 1;
    }
    if (strcasecmp(object_name, "sibur") == 0) {
        tile->tile_ressources->sibur += 1;
        map->ressources_left->sibur += 1;
    }
    add_tile_ressource_and_map_ressource_2(tile, object_name, map);
}

void log_take_object(player_info_t *player, char *object_name,
    size_t number_of_object)
{
    log_message("log/ai_commands.log", GREEN, "[%d] Take %s\n", player->fd,
        object_name);
    log_message("log/ai_commands.log", GREEN, "[%d] Number of object: %lu\n",
        player->fd, number_of_object);
}
