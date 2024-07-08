/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** execute_objects.c
*/

#include "execute_commands.h"
#include "execute_instructions_commands.h"

int convert_object_name_to_enum(char *object_name)
{
    if (strcasecmp(object_name, "food") == 0)
        return 0;
    if (strcasecmp(object_name, "linemate") == 0)
        return 1;
    if (strcasecmp(object_name, "deraumere") == 0)
        return 2;
    if (strcasecmp(object_name, "sibur") == 0)
        return 3;
    if (strcasecmp(object_name, "mendiane") == 0)
        return 4;
    if (strcasecmp(object_name, "phiras") == 0)
        return 5;
    if (strcasecmp(object_name, "thystame") == 0)
        return 6;
    return -1;
}

void remove_an_object_from_tile(tile_t *tile, char *object_name)
{
    if (strcasecmp(object_name, "food") == 0)
        remove_tile_ressource_and_map_ressource(tile, object_name);
    if (strcasecmp(object_name, "linemate") == 0)
        remove_tile_ressource_and_map_ressource(tile, object_name);
    if (strcasecmp(object_name, "deraumere") == 0)
        remove_tile_ressource_and_map_ressource(tile, object_name);
    if (strcasecmp(object_name, "sibur") == 0)
        remove_tile_ressource_and_map_ressource(tile, object_name);
    if (strcasecmp(object_name, "mendiane") == 0)
        remove_tile_ressource_and_map_ressource(tile, object_name);
    if (strcasecmp(object_name, "phiras") == 0)
        remove_tile_ressource_and_map_ressource(tile, object_name);
    if (strcasecmp(object_name, "thystame") == 0)
        remove_tile_ressource_and_map_ressource(tile, object_name);
}

static void remove_an_object_player_inventory(player_info_t *player,
    char *object_name)
{
    if (strcasecmp(object_name, "food") == 0)
        player->inventory->food -= 1;
    if (strcasecmp(object_name, "linemate") == 0)
        player->inventory->linemate -= 1;
    if (strcasecmp(object_name, "deraumere") == 0)
        player->inventory->deraumere -= 1;
    if (strcasecmp(object_name, "sibur") == 0)
        player->inventory->sibur -= 1;
    if (strcasecmp(object_name, "mendiane") == 0)
        player->inventory->mendiane -= 1;
    if (strcasecmp(object_name, "phiras") == 0)
        player->inventory->phiras -= 1;
    if (strcasecmp(object_name, "thystame") == 0)
        player->inventory->thystame -= 1;
}

static void add_an_object_player_inventory(player_info_t *player,
    char *object_name)
{
    log_message("log/take_object.log", GREEN, "Take OK\n");
    if (strcasecmp(object_name, "food") == 0)
        player->inventory->food += 1;
    if (strcasecmp(object_name, "linemate") == 0)
        player->inventory->linemate += 1;
    if (strcasecmp(object_name, "deraumere") == 0)
        player->inventory->deraumere += 1;
    if (strcasecmp(object_name, "sibur") == 0)
        player->inventory->sibur += 1;
    if (strcasecmp(object_name, "mendiane") == 0)
        player->inventory->mendiane += 1;
    if (strcasecmp(object_name, "phiras") == 0)
        player->inventory->phiras += 1;
    if (strcasecmp(object_name, "thystame") == 0)
        player->inventory->thystame += 1;
}

static char *get_object_name(char *object_name)
{
    object_name = remove_special_chars(object_name);
    return object_name;
}

//take object which is gonna see if the tile on the player x y has
//the object (the name of it) and then take it (ok\n) or not (ko\n)
static void take_object(player_info_t *player, char *object_name)
{
    zappy_t *myzappy = (zappy_t *)global_zappy;
    tile_t *current_tile = find_tile_by_pos(myzappy->server->map->tiles,
        player->x, player->y);
    char *new_object_name = get_object_name(object_name);
    size_t number_of_object = find_object_quantity_by_name(current_tile,
        new_object_name);
    int ressource_enum = convert_object_name_to_enum(new_object_name);

    log_take_object(player, new_object_name, number_of_object);
    if (number_of_object > 0) {
        add_an_object_player_inventory(player, new_object_name);
        remove_an_object_from_tile(current_tile, new_object_name);
        send_ok_take(player, ressource_enum);
        remove_from_garbage(new_object_name);
    } else {
        send_data(player->fd, "ko\n");
        remove_from_garbage(new_object_name);
        log_message("log/take_object.log", RED, "Take KO\n");
    }
}

void execute_take_object_command(player_info_t *player, char *arg)
{
    char *message = NULL;

    if (player->timer_action <= 0) {
        if (arg == NULL) {
            send_data(player->fd, "ko\n");
            return;
        }
        new_alloc_asprintf(&message, "bct %d %d\n", player->x, player->y);
        execute_bct_command(NULL, message);
        take_object(player, arg);
        log_message("log/take_object.log", GREEN, "Take OK\n");
        log_message("log/take_object.log", GREEN, "player x: %d, y: %d\n",
            player->x, player->y);
    }
}

static void add_an_object(tile_t *tile, char *object_name)
{
    if (strcasecmp(object_name, "food") == 0)
        add_tile_ressource_and_map_ressource(tile, object_name);
    if (strcasecmp(object_name, "linemate") == 0)
        add_tile_ressource_and_map_ressource(tile, object_name);
    if (strcasecmp(object_name, "deraumere") == 0)
        add_tile_ressource_and_map_ressource(tile, object_name);
    if (strcasecmp(object_name, "sibur") == 0)
        add_tile_ressource_and_map_ressource(tile, object_name);
    if (strcasecmp(object_name, "mendiane") == 0)
        add_tile_ressource_and_map_ressource(tile, object_name);
    if (strcasecmp(object_name, "phiras") == 0)
        add_tile_ressource_and_map_ressource(tile, object_name);
    if (strcasecmp(object_name, "thystame") == 0)
        add_tile_ressource_and_map_ressource(tile, object_name);
}

static void set_object(player_info_t *player, char *object_name)
{
    zappy_t *myzappy = (zappy_t *)global_zappy;
    tile_t *current_tile = find_tile_by_pos(myzappy->server->map->tiles,
        player->x, player->y);
    char *new_object_name = get_object_name(object_name);
    size_t player_object_quantity =
        find_object_quantity_player_inventory(player, new_object_name);
    int ressource_enum = convert_object_name_to_enum(new_object_name);

    if (player_object_quantity > 0) {
        add_an_object(current_tile, new_object_name);
        remove_an_object_player_inventory(player, new_object_name);
        send_ok_set(player, ressource_enum);
    } else {
        log_message("log/set_object.log", RED, "Set KO\n");
    }
}

void execute_set_object_command(player_info_t *player, char *arg)
{
    if (player->timer_action <= 0) {
        if (arg == NULL) {
            send_data(player->fd, "ko\n");
            return;
        }
        set_object(player, arg);
        log_message("log/set_object.log", GREEN, "Set OK\n");
        log_message("log/set_object.log", GREEN, "player x: %d, y: %d\n",
            player->x, player->y);
    }
}
