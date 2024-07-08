/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** loop
*/

#include "zappy.h"
#include "map_regen.h"
#include "linked_list_utils.h"
#include "print_server_info.h"
#include "execute_commands.h"
#include "math.h"
#include "garbage_collector.h"

void exec_misc_command(player_info_t *player, char *command, char *arg)
{
    if (strcmp(command, "Inventory") == 0)
        return execute_inventory_command(player, arg);
    if (strcmp(command, "Broadcast") == 0)
        return execute_broadcast_command(player, arg);
    if (strcmp(command, "Connect_nbr") == 0)
        return execute_connect_nbr_command(player, arg);
    if (strcmp(command, "Fork") == 0)
        return execute_fork_command(player, arg);
    if (strcmp(command, "Eject") == 0)
        return execute_eject_command(player, arg);
    if (strcmp(command, "Set") == 0)
        return execute_set_object_command(player, arg);
    if (strcmp(command, "Incantation") == 0)
        return execute_incantation_command(player, arg);
}

void exec_frequent_commands(player_info_t *player, char *command, char *arg)
{
    printf("[%d] Command: %s\n", player->fd, command);
    if (strcmp(command, "Forward") == 0)
        return execute_forward_command(player, arg);
    if (strcmp(command, "Right") == 0)
        return execute_turn_right_command(player, arg);
    if (strcmp(command, "Left") == 0)
        return execute_turn_left_command(player, arg);
    if (strcmp(command, "Look") == 0)
        return execute_look_command(player, arg);
    if (strcmp(command, "Take") == 0)
        return execute_take_object_command(player, arg);
    exec_misc_command(player, command, arg);
}

static void free_exec_command(exec_command_t *exec_command)
{
    if (exec_command->command != NULL) {
        remove_from_garbage(exec_command->command);
    }
    if (exec_command->arg != NULL) {
        remove_from_garbage(exec_command->arg);
    }
}

void handle_instructions(zappy_t *zappy, player_info_t *p)
{
    (void) zappy;
    if (p->timer_action <= 0 && p->exec_command->command != NULL) {
        log_message("log/player_pos.log", RED, "Player %d: x=%d y=%d\n",
            p->fd, p->x, p->y);
        exec_frequent_commands(p, p->exec_command->command,
            p->exec_command->arg);
        free_exec_command(p->exec_command);
        p->exec_command->command = NULL;
        p->exec_command->arg = NULL;
    }
}

void game_loop(zappy_t *zappy)
{
    update_and_regenerate_map(zappy);
    if (!exit_status)
        set_lowest_timeout(zappy);
    server_monitor(zappy);
    server_connections(zappy);
    server_commands(zappy);
    server_stacks(zappy);
    if (winning_team()) {
        free_all_garbage_collector();
    }
}

void zappy_loop(zappy_t *zappy)
{
    struct timespec start;
    struct timespec current;
    double lastT;
    double currentT;
    double elapsed;

    clock_gettime(CLOCK_MONOTONIC, &start);
    lastT = start.tv_sec + start.tv_nsec / 1e9;
    print_beginning_info(zappy);
    while (!exit_status) {
        game_loop(zappy);
        clock_gettime(CLOCK_MONOTONIC, &current);
        currentT = current.tv_sec + current.tv_nsec / 1e9;
        elapsed = currentT - lastT;
        zappy->server->processor_time += elapsed;
        decrement_real_player_timers(zappy, elapsed);
        decrement_game_timers(zappy, elapsed);
        lastT = currentT;
    }
    free_all_garbage_collector();
}
