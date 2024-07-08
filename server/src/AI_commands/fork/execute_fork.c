/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** execute_fork.c
*/

#include "execute_commands.h"
#include "execute_instructions_commands.h"

static team_egg_t *create_egg(player_info_t *player)
{
    team_egg_t *egg = new_alloc(sizeof(team_egg_t));
    zappy_t *myzappy = (zappy_t *) global_zappy;

    myzappy->server->game->egg_max_id++;
    egg->id = myzappy->server->game->egg_max_id;
    egg->x = player->x;
    egg->y = player->y;
    if (myzappy->gui->fd != -1) {
        send_enw_event(egg->id, player->fd, egg->x, egg->y);
    }
    return (egg);
}

static void fork_player(player_info_t *player)
{
    zappy_t *my_zappy = (zappy_t *)global_zappy;
    team_info_t *team =
        find_team_by_name(my_zappy->server->game->teams, player->team_name);
    team_egg_t *new_egg = create_egg(player);

    if (team == NULL || new_egg == NULL)
        return;
    new_egg->next = team->eggs;
    team->eggs = new_egg;
    team->slotAvailable = team->slotAvailable + 1;
    team->slotMax = team->slotMax + 1;
    log_message("log/fork.log", GREEN, "[%d] Fork OK",
        player->fd);
    log_message("log/fork.log", GREEN, "Team: %s\n", team->name);
    log_message("log/fork.log", GREEN, "slotAvailable: %d\n",
        team->slotAvailable);
    log_message("log/fork.log", GREEN, "slotMax: %d\n", team->slotMax);
    send_pfk_event(player);
    send_data(player->fd, "ok\n");
}

/*The execution of this command leads to the production of an egg.
Once it’s layed, the player who has layed it can take care of their business.
Once the egg is layed, a new slot is added to the team.
This operation authorizes a new client to be connected.
The connect_nbr command sends back the number of connections that are
//underway and authorized for this family
*/
void execute_fork_command(player_info_t *player, char *arg)
{
    (void)arg;
    if (player->timer_action <= 0) {
        fork_player(player);
        log_message("log/fork.log", GREEN, "[%d] Fork OK\n",
            player->fd);
    }
}
