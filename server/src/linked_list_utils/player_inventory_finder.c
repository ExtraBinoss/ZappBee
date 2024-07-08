/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** player_inventory_finder.c
*/

#include "linked_list_utils.h"

const char *ressources_names[] = {
    "FOOD",
    "LINEMATE",
    "DERAUMERE",
    "SIBUR",
    "MENDIANE",
    "PHIRAS",
    "THYSTAME"
};

size_t find_object_quantity_by_name(tile_t *tile, const char *object_name)
{
    if (strcasecmp(object_name, "food") == 0)
        return tile->tile_ressources->food;
    if (strcasecmp(object_name, "linemate") == 0)
        return tile->tile_ressources->linemate;
    if (strcasecmp(object_name, "deraumere") == 0)
        return tile->tile_ressources->deraumere;
    if (strcasecmp(object_name, "sibur") == 0)
        return tile->tile_ressources->sibur;
    if (strcasecmp(object_name, "mendiane") == 0)
        return tile->tile_ressources->mendiane;
    if (strcasecmp(object_name, "phiras") == 0)
        return tile->tile_ressources->phiras;
    if (strcasecmp(object_name, "thystame") == 0)
        return tile->tile_ressources->thystame;
    return 0;
}

size_t find_object_quantity_player_inventory(player_info_t *player,
    const char *object_name)
{
    if (strcasecmp(object_name, "food") == 0)
        return player->inventory->food;
    if (strcasecmp(object_name, "linemate") == 0)
        return player->inventory->linemate;
    if (strcasecmp(object_name, "deraumere") == 0)
        return player->inventory->deraumere;
    if (strcasecmp(object_name, "sibur") == 0)
        return player->inventory->sibur;
    if (strcasecmp(object_name, "mendiane") == 0)
        return player->inventory->mendiane;
    if (strcasecmp(object_name, "phiras") == 0)
        return player->inventory->phiras;
    if (strcasecmp(object_name, "thystame") == 0)
        return player->inventory->thystame;
    return 0;
}
