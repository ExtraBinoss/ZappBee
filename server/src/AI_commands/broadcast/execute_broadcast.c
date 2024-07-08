/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** execute_broadcast.c
*/

#include "execute_commands.h"

static int get_direction_y_move_minus_one(player_info_t *receiver)
{
    if (receiver->direction == UP)
        return 5;
    if (receiver->direction == DOWN)
        return 1;
    if (receiver->direction == LEFT)
        return 3;
    if (receiver->direction == RIGHT)
        return 7;
    return 0;
}

static int get_direction_y_move_one(player_info_t *receiver)
{
    if (receiver->direction == UP)
        return 1;
    if (receiver->direction == DOWN)
        return 5;
    if (receiver->direction == LEFT)
        return 7;
    if (receiver->direction == RIGHT)
        return 3;
    return 0;
}

static int get_direction_x_move_one(player_info_t *receiver)
{
    if (receiver->direction == UP)
        return 7;
    if (receiver->direction == DOWN)
        return 3;
    if (receiver->direction == LEFT)
        return 5;
    if (receiver->direction == RIGHT)
        return 1;
    return 0;
}

static int get_direction_x_move_minus_one(player_info_t *receiver)
{
    if (receiver->direction == UP)
        return 3;
    if (receiver->direction == DOWN)
        return 7;
    if (receiver->direction == LEFT)
        return 1;
    if (receiver->direction == RIGHT)
        return 5;
    return 0;
}

static int get_shortest_dir(int emitter, int receiver, int max)
{
    if (emitter == receiver)
        return 0;
    if (emitter > receiver) {
        if (max - emitter + receiver < emitter - receiver)
            return -1;
        return 1;
    }
    if (receiver > emitter) {
        if (max - receiver + emitter < receiver - emitter)
            return 1;
        return -1;
    }
    return 84;
}

int fuse_direction(int dy, int dx)
{
    if (dy == 0 || dx == 0)
        return (dy + dx);
    if ((dy == 1 && dx == 7) || (dy == 7 && dx == 1))
        return 8;
    return (dy + dx) / 2;
}

int calculate_direction(player_info_t *emitter, player_info_t *receiver)
{
    int MAP_WIDTH = global_zappy->server->game->width;
    int MAP_HEIGHT = global_zappy->server->game->height;
    int my = get_shortest_dir(emitter->y, receiver->y, MAP_WIDTH);
    int mx = get_shortest_dir(emitter->x, receiver->x, MAP_HEIGHT);
    int dy = 0;
    int dx = 0;

    if (my != 0) {
        if (my == -1)
            dy = get_direction_y_move_minus_one(receiver);
        else
            dy = get_direction_y_move_one(receiver);
    }
    if (mx != 0) {
        if (mx == -1)
            dx = get_direction_x_move_minus_one(receiver);
        else
            dx = get_direction_x_move_one(receiver);
    }
    return fuse_direction(dy, dx);
}

void broadcast_direction(player_info_t *player,
    player_info_t *tmp, char *text_to_broadcast)
{
    int direction = 0;
    char *message = NULL;

    if (tmp->x != player->x || tmp->y != player->y) {
        direction = calculate_direction(player, tmp);
        new_alloc_asprintf(&message, "message %d, %s\n",
            direction, text_to_broadcast);
        send_data(tmp->fd, message);
        remove_from_garbage(message);
        message = NULL;
    } else {
        log_message("log/broadcast.log", BLUE, "[%d] GG YOU ARE THE BEST\n",
            tmp->fd);
        new_alloc_asprintf(&message, "message 0, %s\n", text_to_broadcast);
        send_data(tmp->fd, message);
        remove_from_garbage(message);
        message = NULL;
    }
}

void broadcast_message(player_info_t *player, char *text_to_broadcast)
{
    game_t *game = (game_t *)global_zappy->server->game;

    for (player_info_t *tmp = game->players; tmp; tmp = tmp->next) {
        if (tmp->is_alive == false)
            continue;
        if (player->is_alive == false)
            return;
        if (tmp->fd == player->fd) {
            send_data(player->fd, "ok\n");
        } else {
            log_message("log/broadcast_player_position.log", GREEN,
            "[%d] [Px: %d Py: %d], tmp: %d, [%d, %d]\n",
                player->fd, player->x, player->y, tmp->fd, tmp->x, tmp->y);
            broadcast_direction(player, tmp, text_to_broadcast);
        }
    }
    send_pbc_event(player, text_to_broadcast);
}

void execute_broadcast_command(player_info_t *player, char *arg)
{
    char *text_to_broadcast = strtok(arg, "\n");

    if (player->timer_action <= 0) {
        log_message("log/broadcast.log", BLUE, "[%d] Broadcast: %s\n",
            player->fd, text_to_broadcast);
        broadcast_message(player, text_to_broadcast);
        log_message("log/broadcast.log", BLUE, "[%d] Broadcast OK\n",
            player->fd);
    }
}
