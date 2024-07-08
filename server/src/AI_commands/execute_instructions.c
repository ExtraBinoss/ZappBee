/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** execute_instructions
*/

#include "zappy.h"
#include "network_headers/network_stack.h"
#include "network_headers/network_transactions.h"
#include "instructions_headers/execute_instructions_commands.h"
#include "execute_commands.h"

static bool instructions_starts_with(char *instruction, char *start)
{
    if (instruction == NULL || start == NULL)
        return false;
    for (int i = 0; start[i] != '\0'; i++) {
        if (instruction[i] != start[i])
            return false;
    }
    return true;
}

static bool is_players_frozen(player_info_t *players)
{
    for (player_info_t *tmp = players; tmp; tmp = tmp->next) {
        if (tmp->is_frozen)
            return true;
    }
    return false;
}

void execute_gui_instructions(char *instruction)
{
    server_t *server = (server_t *)global_zappy->server;

    if (instructions_starts_with(instruction, "ppo"))
        execute_ppo_command(server->game->players, instruction);
    if (instructions_starts_with(instruction, "plv"))
        execute_plv_command(server->game->players, instruction);
    if (instructions_starts_with(instruction, "pin"))
        execute_pin_command(server->game->players, instruction);
    if (instructions_starts_with(instruction, "msz"))
        execute_msz_command(server->game->players, instruction);
    if (instructions_starts_with(instruction, "bct"))
        execute_bct_command(server->game->players, instruction);
    if (instructions_starts_with(instruction, "mct"))
        execute_mct_command(server->game->players, instruction);
    if (instructions_starts_with(instruction, "tna"))
        execute_tna_command(server->game->players, instruction);
    if (instructions_starts_with(instruction, "sgt"))
        execute_sgt_command(server->game->players, instruction);
    if (instructions_starts_with(instruction, "sst"))
        execute_sst_command(server->game->players, instruction);
}

static void execute_ai_instructions_2(server_t *server, char *instruction,
    player_info_t *current_player)
{
    (void)server;
    if (instructions_starts_with(instruction, "Fork"))
        execute_fork_command(current_player, NULL);
    if (instructions_starts_with(instruction, "Eject"))
        execute_eject_command(current_player, NULL);
    if (instructions_starts_with(instruction, "Take"))
        execute_take_object_command(current_player, instruction);
    if (instructions_starts_with(instruction, "Set"))
        execute_set_object_command(current_player, instruction);
    if (instructions_starts_with(instruction, "Incantation"))
        execute_incantation_command(current_player, NULL);
}

static void execute_ai_instructions_1(server_t *server,
    char *instruction, player_info_t *current_player)
{
    (void)server;
    if (instructions_starts_with(instruction, "Forward"))
        execute_forward_command(current_player, NULL);
    if (instructions_starts_with(instruction, "Right"))
        execute_turn_right_command(current_player, NULL);
    if (instructions_starts_with(instruction, "Left"))
        execute_turn_left_command(current_player, NULL);
    if (instructions_starts_with(instruction, "Look"))
        execute_look_command(current_player, NULL);
    if (instructions_starts_with(instruction, "Inventory"))
        execute_inventory_command(current_player, NULL);
    if (instructions_starts_with(instruction, "Broadcast"))
        execute_broadcast_command(current_player, instruction);
    if (instructions_starts_with(instruction, "Connect_nbr"))
        execute_connect_nbr_command(current_player, NULL);
}

void execute_ai_instructions(char *instruction, client_t *current_client,
    player_info_t *current_player)
{
    server_t *server = (server_t *)global_zappy->server;

    (void)current_client;
    if (instruction == NULL)
        return;
    if (is_players_frozen(server->game->players)) {
        send_data(current_player->fd, "ko\n");
        return;
    }
    if (current_player == NULL || current_client == NULL)
        return;
    execute_ai_instructions_1(server, instruction, current_player);
    execute_ai_instructions_2(server, instruction, current_player);
}
