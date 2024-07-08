/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** server_connections
*/

#include "zappy.h"
#include "network_headers/network_transactions.h"
#include "execute_instructions_commands.h"
#include "events.h"

static player_inventory_t *init_inventory(player_info_t *player)
{
    player->inventory = new_alloc_calloc(sizeof(player_inventory_t));
    player->inventory->food = 10;
    player->inventory->linemate = 0;
    player->inventory->deraumere = 0;
    player->inventory->sibur = 0;
    player->inventory->mendiane = 0;
    player->inventory->phiras = 0;
    player->inventory->thystame = 0;
    return player->inventory;
}

static player_info_t *init_player(player_info_t *player,
    int fd, int team_id, char *team_name)
{
    zappy_t *zappy = (zappy_t *)global_zappy;

    printf("Player initialized\n");
    player->team_id = team_id;
    player->team_name = new_alloc_str(team_name);
    player->fd = fd;
    player->timer_action = 0;
    player->timer_death = 126 / zappy->server->game->freq;
    player->level = 1;
    player->lastT = 0;
    player->elapsed_time = 0;
    player->is_alive = true;
    player->is_frozen = false;
    player->inventory = init_inventory(player);
    player->direction = 0;
    player->exec_command = new_alloc(sizeof(exec_command_t));
    player->exec_command->command = NULL;
    player->exec_command->arg = NULL;
    return player;
}

void add_player_to_team(zappy_t *zappy, int team_id, client_t *new_client)
{
    team_info_t *tmp = zappy->server->game->teams;
    player_info_t *player = new_alloc_calloc(sizeof(player_info_t));

    new_client->next = zappy->IA->clients;
    new_client->stack = NULL;
    zappy->IA->clients = new_client;
    while (tmp) {
        if (tmp->ID == team_id) {
            init_player(player, new_client->fd, team_id, tmp->name);
            player->next = zappy->server->game->players;
            zappy->server->game->players = player;
            set_player_spawnpoint(player, tmp);
            send_pnw_event(player);
            break;
        }
        tmp = tmp->next;
    }
}

static void data_send_gui(void)
{
    server_t *myzappy = (server_t *) global_zappy->server;
    team_info_t *team = (team_info_t *) global_zappy->server->game->teams;
    char *repsonse = NULL;

    new_alloc_asprintf(&repsonse, "msz %d %d\n", myzappy->map->width,
        myzappy->map->height);
    send_data(global_zappy->gui->fd, repsonse);
    execute_mct_command(NULL, NULL);
    repsonse = NULL;
    while (team != NULL) {
        new_alloc_asprintf(&repsonse, "tna %s\n", team->name);
        send_data(global_zappy->gui->fd, repsonse);
        team = team->next;
    }
}

void client_add(zappy_t *zappy, int new_socket, struct sockaddr_in *ca)
{
    int auth_status = authentification(zappy, new_socket);
    client_t *new_client;

    if (auth_status == -1) {
        send_data(new_socket, "KO\n");
        close(new_socket);
    }
    if (auth_status == 0) {
        zappy->gui->fd = new_socket;
        zappy->gui->addr = *ca;
        zappy->gui->stack = NULL;
        data_send_gui();
    }
    if (auth_status <= 0)
        return;
    new_client = new_alloc_calloc(sizeof(client_t));
    new_client->fd = new_socket;
    new_client->addr = *ca;
    new_client->stack = NULL;
    add_player_to_team(zappy, auth_status, new_client);
}

int del_client(client_t *tmp, client_t *prev, zappy_t *zappy)
{
    if (prev)
        prev->next = tmp->next;
    else
        zappy->IA->clients = tmp->next;
    remove_from_garbage(tmp);
    return 1;
}

void remove_client(zappy_t *zappy, int fd)
{
    client_t *tmp = zappy->IA->clients;
    client_t *prev = NULL;
    int test = 0;

    while (tmp) {
        if (tmp->fd == fd) {
            test = del_client(tmp, prev, zappy);
            break;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    if (test == 0 && zappy->gui->fd == fd) {
        zappy->gui->fd = -1;
        zappy->gui->addr.sin_family = -1;
    }
    close(fd);
}

// ca = Client address
void server_connections(zappy_t *zappy)
{
    struct sockaddr_in ca;
    socklen_t l;
    int new_socket;

    if (FD_ISSET(zappy->server->fd, &zappy->server->read_fds)) {
        l = sizeof(ca);
        new_socket = accept(zappy->server->fd, (struct sockaddr *)&ca, &l);
        if (new_socket < 0) {
            log_message("log/error_accept.log", RED, "Accept failed");
            return;
        }
        client_add(zappy, new_socket, &ca);
    }
}
