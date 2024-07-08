/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** execute_bct_command.c
*/

#include "execute_instructions_commands.h"

static void fill_asprintf_bct(char **response, tile_t *tile, int x, int y)
{
    new_alloc_asprintf(response, "bct %d %d %ld %ld %ld %ld %ld %ld %ld\n",
        x, y,
        tile->tile_ressources->food,
        tile->tile_ressources->linemate, tile->tile_ressources->deraumere,
        tile->tile_ressources->sibur, tile->tile_ressources->mendiane,
        tile->tile_ressources->phiras, tile->tile_ressources->thystame);
}

void execute_bct_command(player_info_t *player, char *instruction)
{
    zappy_t *myzappy = (zappy_t *)global_zappy;
    game_t *game = myzappy->server->game;
    tile_t *tile = NULL;
    char *response = NULL;
    int x = 0;
    int y = 0;

    (void)player;
    sscanf(instruction, "bct %d %d", &x, &y);
    if (x < 0 || x >= game->width || y < 0 || y >= game->height) {
        send_data(myzappy->gui->fd, "sbp\n");
        return;
    }
    tile = find_tile_by_pos(myzappy->server->map->tiles, x, y);
    fill_asprintf_bct(&response, tile, x, y);
    send_data(myzappy->gui->fd, response);
}
