/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** object_print.c
*/

#include "execute_commands.h"
#include "execute_instructions_commands.h"

void send_ok_take(player_info_t *player, int ressource_enum)
{
    char *message = NULL;

    send_pgt_event(player, ressource_enum);
    send_data(player->fd, "ok\n");
    new_alloc_asprintf(&message, "bct %d %d\n", player->x, player->y);
    execute_bct_command(NULL, message);
}

void send_ok_set(player_info_t *player, int ressource_enum)
{
    char *message = NULL;

    send_pdr_event(player, ressource_enum);
    new_alloc_asprintf(&message, "bct %d %d\n", player->x, player->y);
    execute_bct_command(NULL, message);
    send_data(player->fd, "ok\n");
}
