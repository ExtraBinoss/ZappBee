/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** set_timer_instructions.c
*/

#include "set_timer_instructions.h"
#include "execute_commands.h"

static void send_ko_event(player_info_t *p, int nb_players_on_tile,
    int nb_players_required_on_tile)
{
    tile_t *t = find_tile_by_pos(global_zappy->server->map->tiles, p->x, p->y);

    log_message("log/incantation.log", RED, "Incantation failed");
    log_message("log/incantation.log", RED, "nb_players_on_tile: %d |",
        nb_players_on_tile);
    log_message("log/incantation.log", RED, "nb_players_required_tile: %d\n",
        nb_players_required_on_tile);
    printf("[%d] Incantation failed for level %ld\n", p->fd, p->level + 1);
    printf("[%d] Incantation failed, players required on tile: %d/%d\n",
    p->fd, nb_players_on_tile, nb_players_required_on_tile);
    printf("[%d] Ressources on tile: %ld/%ld/%ld/%ld/%ld/%ld\n", p->fd,
        t->tile_ressources->linemate, t->tile_ressources->deraumere,
        t->tile_ressources->sibur, t->tile_ressources->mendiane,
        t->tile_ressources->phiras, t->tile_ressources->thystame);
    send_data(p->fd, "ko\n");
    p->timer_action = 0;
    p->elapsed_time = 0;
    p->lastT = 0;
}

static bool do_incantation_checks(player_info_t *player)
{
    map_t *map = (map_t *)global_zappy->server->map;
    int nb_players_on_tile = check_number_of_players_on_tile(player);
    int nb_players_required_on_tile =
        check_player_current_level(player->level);
    char *player_fds = get_player_fds_on_tile(player);
    char *response = NULL;

    if (check_ressources_required(player, map) == false
        || nb_players_on_tile < nb_players_required_on_tile) {
        send_ko_event(player, nb_players_on_tile, nb_players_required_on_tile);
        return false;
    }
    send_pic_event((int[3]) {player->x, player->y, player->level},
        player_fds);
    new_alloc_asprintf(&response, "Elevation underway\n");
    send_data(player->fd, response);
    freeze_players_on_tile(player, global_zappy->server->game, true);
    remove_from_garbage(player_fds);
    return true;
}

void set_incantation_timer(player_info_t *player, char *arg)
{
    (void)arg;
    if (player->timer_action == 0) {
        if (do_incantation_checks(player) == false)
            return;
        player->timer_action = 300 / global_zappy->server->game->freq;
        player->elapsed_time = 0;
        player->lastT = 0;
        player->exec_command->command = new_alloc_str("Incantation");
        player->exec_command->arg = NULL;
    }
}

void set_broadcast_timer(player_info_t *player, char *arg)
{
    (void)arg;
    if (player->timer_action == 0) {
        player->timer_action = 7 / global_zappy->server->game->freq;
        player->elapsed_time = 0;
        player->lastT = 0;
        player->exec_command->command = new_alloc_str("Broadcast");
        player->exec_command->arg = new_alloc_str(arg);
    }
}

void set_connect_nbr_timer(player_info_t *player, char *arg)
{
    (void)arg;
    if (player->timer_action == 0) {
        player->timer_action = 7 / global_zappy->server->game->freq;
        player->elapsed_time = 0;
        player->lastT = 0;
        player->exec_command->command = new_alloc_str("Connect_nbr");
        player->exec_command->arg = NULL;
    }
}

void set_direction_timer(player_info_t *player, char *arg)
{
    (void)arg;
    if (player->timer_action == 0) {
        player->timer_action = 7 / global_zappy->server->game->freq;
        player->elapsed_time = 0;
        player->lastT = 0;
        player->exec_command->command = new_alloc_str("Direction");
        player->exec_command->arg = NULL;
    }
}

void set_eject_timer(player_info_t *player, char *arg)
{
    (void)arg;
    if (player->timer_action == 0) {
        player->timer_action = 7 / global_zappy->server->game->freq;
        player->elapsed_time = 0;
        player->lastT = 0;
        player->exec_command->command = new_alloc_str("Eject");
        player->exec_command->arg = NULL;
    }
}
