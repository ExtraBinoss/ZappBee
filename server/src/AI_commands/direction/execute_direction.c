/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** execute_forward.c
*/

#include "execute_commands.h"
#include "execute_instructions_commands.h"
//forward will add xy-1 (move up one tile) to the player's position

static void forward(player_info_t *player, game_t *game)
{
    if (player->direction == UP) {
        player->y += 1;
        if (player->y >= game->height)
            player->y = 0;
    }
    if (player->direction == DOWN) {
        player->y -= 1;
        if (player->y < 0)
            player->y = game->height - 1;
    }
    if (player->direction == LEFT) {
        player->x -= 1;
        if (player->x < 0)
            player->x = game->width - 1;
    }
    if (player->direction == RIGHT) {
        player->x += 1;
        if (player->x >= game->width)
            player->x = 0;
    }
}

static void turn_right(player_info_t *player)
{
    if (player->direction == UP) {
        player->direction = RIGHT;
        return;
    }
    if (player->direction == RIGHT) {
        player->direction = DOWN;
        return;
    }
    if (player->direction == DOWN) {
        player->direction = LEFT;
        return;
    }
    if (player->direction == LEFT) {
        player->direction = UP;
        return;
    }
}

static void turn_left(player_info_t *player)
{
    if (player->direction == UP) {
        player->direction = LEFT;
        return;
    }
    if (player->direction == LEFT) {
        player->direction = DOWN;
        return;
    }
    if (player->direction == DOWN) {
        player->direction = RIGHT;
        return;
    }
    if (player->direction == RIGHT) {
        player->direction = UP;
        return;
    }
}

static void print_current_position(player_info_t *player)
{
    char *player_fd_char = NULL;

    log_message("log/player_movement.log", GREEN, "[%d] After position: %d",
    player->fd);
    log_message("log/player_movement.log", GREEN, ", %d, ", player->x);
    log_message("log/player_movement.log", GREEN, "%d\n", player->y);
    new_alloc_asprintf(&player_fd_char, "ppo #%d\n", player->fd);
    execute_ppo_command(player, player_fd_char);
}

void execute_forward_command(player_info_t *player, char *arg)
{
    zappy_t *myzappy = (zappy_t *)global_zappy;

    (void)arg;
    if (player->timer_action <= 0) {
        log_message("log/player_movement.log", RED, "[%d] Before position: %d,"
        "%d\n", player->fd, player->x, player->y);
        forward(player, myzappy->server->game);
        print_current_position(player);
        send_data(player->fd, "ok\n");
        log_message("log/player_movement.log", GREEN, "[%d] Forward OK\n",
            player->fd);
    }
}

void execute_turn_right_command(player_info_t *player, char *arg)
{
    (void)arg;
    if (player->timer_action <= 0) {
        turn_right(player);
        send_data(player->fd, "ok\n");
        log_message("log/player_movement.log", GREEN, "[%d] Right OK\n",
            player->fd);
    }
}

void execute_turn_left_command(player_info_t *player, char *arg)
{
    (void)arg;
    if (player->timer_action <= 0) {
        turn_left(player);
        send_data(player->fd, "ok\n");
        log_message("log/player_movement.log", GREEN, "[%d] Left OK\n",
            player->fd);
    }
}
