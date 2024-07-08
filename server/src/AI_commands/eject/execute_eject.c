/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** execute_eject.c
*/

#include "execute_commands.h"

void ejection_move_player(player_info_t *player, zappy_t *myzappy)
{
    if (player->direction == 1)
        player->x = (player->x + 1) % myzappy->server->map->width;
    if (player->direction == 2)
        player->y = (player->y + 1) % myzappy->server->map->height;
    if (player->direction == 3)
        player->x = (player->x - 1 + myzappy->server->map->width)
            % myzappy->server->map->width;
    if (player->direction == 4)
        player->y = (player->y - 1 +
            myzappy->server->map->height) % myzappy->server->map->height;
}

team_egg_t *try_breaking_egg(team_egg_t *egg, tile_t *tile,
    team_info_t *team, int fd)
{
    team_egg_t *next_egg = NULL;

    if (egg->x == tile->x && egg->y == tile->y) {
        team->slotAvailable--;
        team->slotMax--;
        next_egg = egg->next;
        if (fd != -1) {
            send_edi_event(fd, egg->id);
        }
        remove_from_garbage(egg);
    } else {
        next_egg = egg->next;
    }
    return next_egg;
}

void break_eggs(tile_t *tile, zappy_t *z)
{
    team_egg_t *egg = NULL;

    for (team_info_t *team = z->server->game->teams; team; team = team->next) {
        egg = team->eggs;
        while (egg) {
            egg = try_breaking_egg(egg, tile, team, z->gui->fd);
        }
    }
}

void eject(player_info_t *player)
{
    zappy_t *myzappy = (zappy_t *)global_zappy;
    game_t *game = myzappy->server->game;
    tile_t *current_tile =
        find_tile_by_pos(myzappy->server->map->tiles, player->x, player->y);

    for (player_info_t *other_p = game->players;
        other_p; other_p = other_p->next) {
        if ((int)current_tile->x == other_p->x &&
            (int)current_tile->y == other_p->y) {
            ejection_move_player(other_p, myzappy);
            log_message("log/eject.log", GREEN, "[%d] Ejecting player\n",
                other_p->fd);
            send_pex_event(other_p);
            break_eggs(current_tile, myzappy);
        }
    }
    send_data(player->fd, "ok\n");
}

void execute_eject_command(player_info_t *player, char *arg)
{
    (void)arg;
    if (player->timer_action <= 0) {
        eject(player);
        log_message("log/eject.log", GREEN, "[%d] Eject OK\n",
            player->fd);
    }
}
