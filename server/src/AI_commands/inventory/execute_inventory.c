/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** execute_inventory.c
*/

#include "execute_commands.h"
#include "execute_instructions_commands.h"

static void inventory(player_info_t *player)
{
    char *inventory_str = NULL;
    char *fd_str = NULL;

    new_alloc_asprintf(&inventory_str,
        "[food %lu, linemate %lu, deraumere %lu, sibur %lu, mendiane %lu"
        ", phiras %lu, thystame %lu]\n",
        player->inventory->food, player->inventory->linemate,
        player->inventory->deraumere, player->inventory->sibur,
        player->inventory->mendiane, player->inventory->phiras,
        player->inventory->thystame);
    send_data(player->fd, inventory_str);
    log_message("log/inventory.log", GREEN, "[%d] Inventory : %s\n",
        player->fd, inventory_str);
    new_alloc_asprintf(&fd_str, "pin #%d\n", player->fd);
    execute_pin_command(player, fd_str);
}

void execute_inventory_command(player_info_t *player, char *arg)
{
    (void)arg;
    if (player->timer_action <= 0) {
        inventory(player);
        log_message("log/inventory.log", GREEN, "[%d] Inventory OK\n",
            player->fd);
    }
}
