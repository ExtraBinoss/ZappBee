/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** set_time_action.c
*/

#include "execute_commands.h"
#include "set_timer_instructions.h"

set_timer_instruction_t set_instructions[] = {
    {"Incantation", &set_incantation_timer},
    {"Broadcast", &set_broadcast_timer},
    {"Connect_nbr", &set_connect_nbr_timer},
    {"Direction", &set_direction_timer},
    {"Eject", &set_eject_timer},
    {"Fork", &set_fork_timer},
    {"Inventory", &set_inventory_timer},
    {"Look", &set_look_timer},
    {"Set", &set_set_object_timer},
    {"Take", &set_take_object_timer},
    {"Forward", &set_forward_timer},
    {"Right", &set_right_timer},
    {"Left", &set_left_timer},
    {NULL, NULL}
};

void set_timer_instruction(player_info_t *player, char *command)
{
    int len = 0;
    char *arg = NULL;
    char *clean_cmd = remove_special_chars(command);

    for (int i = 0; set_instructions[i].instruction != NULL; i++) {
        len = strlen(set_instructions[i].instruction);
        if (strncmp(set_instructions[i].instruction, command, len) == 0) {
            arg = command[len] == ' ' ? command + len + 1 : NULL;
            printf("[%d] set instruction: [%s]\n", player->fd, clean_cmd);
            set_instructions[i].set_timer(player, arg);
            log_message("log/set_timer.log", GREEN,
                "[%d] set_timer_instruction: [%s]", player->fd, clean_cmd);
            return;
        }
    }
    printf("Command not found: %s\n", clean_cmd);
    return;
}
