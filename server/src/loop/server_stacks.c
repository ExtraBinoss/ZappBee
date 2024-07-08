/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** server_commands
*/

#include "zappy.h"
#include "network_headers/network_stack.h"
#include "network_headers/network_transactions.h"
#include "execute_commands.h"

void parse_gui_commands(gui_t *gui)
{
    char *instruction = NULL;

    instruction = peek_top(gui->stack);
    while (instruction != NULL) {
        execute_gui_instructions(instruction);
        pop_top(&gui->stack);
        instruction = peek_top(gui->stack);
    }
}

static player_info_t *find_player_by_client_fd(int fd)
{
    server_t *server = (server_t *)global_zappy->server;
    player_info_t *current_player = server->game->players;

    while (current_player != NULL) {
        if (current_player == NULL)
            return NULL;
        if (current_player->fd == fd) {
            return current_player;
        }
        current_player = current_player->next;
    }
    return NULL;
}

void parse_ia_commands(zappy_t *zappy)
{
    char *instruction = NULL;
    client_t *current_client = zappy->IA->clients;
    player_info_t *player = NULL;

    while (current_client != NULL) {
        player = find_player_by_client_fd(current_client->fd);
        if (player->timer_action != 0
            || player->exec_command->command != NULL
            || player->is_alive == false) {
            current_client = current_client->next;
            continue;
        }
        instruction = peek_top(current_client->stack);
        if (instruction != NULL) {
            set_timer_instruction(player, instruction);
            pop_top(&current_client->stack);
            instruction = peek_top(current_client->stack);
        }
        current_client = current_client->next;
    }
}

void remove_ia_overload(ia_t *ia)
{
    client_t *current_client = ia->clients;
    int size_stack = 0;

    while (current_client != NULL) {
        size_stack = stack_size(current_client->stack);
        while (size_stack > 10) {
            pop_back(&current_client->stack);
            size_stack--;
        }
        current_client = current_client->next;
    }
}

void server_stacks(zappy_t *zappy)
{
    parse_gui_commands(zappy->gui);
    parse_ia_commands(zappy);
    remove_ia_overload(zappy->IA);
}
