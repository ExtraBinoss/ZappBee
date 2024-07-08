/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** execute_mct_command.c
*/

#include "execute_instructions_commands.h"

void execute_mct_command(player_info_t *player, char *instruction)
{
    zappy_t *myzappy = (zappy_t *)global_zappy;
    tile_t *tile = NULL;
    char *response = NULL;

    (void)player;
    (void)instruction;
    for (int i = 0; i < myzappy->server->game->height; i++) {
        for (int j = 0; j < myzappy->server->game->width; j++) {
            tile = find_tile_by_pos(myzappy->server->map->tiles, j, i);
            new_alloc_asprintf(&response,
                "bct %d %d %ld %ld %ld %ld %ld %ld %ld\n",
                j, i,
                tile->tile_ressources->food, tile->tile_ressources->linemate,
                tile->tile_ressources->deraumere,
                tile->tile_ressources->sibur, tile->tile_ressources->mendiane,
                tile->tile_ressources->phiras,
                tile->tile_ressources->thystame);
            send_data(myzappy->gui->fd, response);
        }
    }
}
