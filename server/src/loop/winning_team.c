/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** winning_team.c
*/

#include "linked_list_utils.h"
#include "game.h"
#include "network_transactions.h"
#include "events.h"

static void send_data_to_all_players_from_team(player_info_t *p,
    team_info_t *current_team, char *str)
{
    while (p != NULL) {
        if (strcmp(p->team_name, current_team->name)
        && p->level >= 8) {
            send_data(p->fd, str);
        }
        p = p->next;
    }
}

static void send_notification_to_gui(zappy_t *myzappy, char *current_team,
    int final_time)
{
    char *str = NULL;

    new_alloc_asprintf(&str, "smg %s %d\n", current_team, final_time);
    send_data(myzappy->gui->fd, str);
}

static bool notify_winner(player_info_t *p,
    team_info_t *current_team, char *str, double final_time)
{
    zappy_t *myzappy = (zappy_t *)global_zappy;

    current_team = myzappy->server->game->teams;
    while (current_team != NULL) {
        if (current_team->ID == p->team_id) {
            new_alloc_asprintf(&str, "win %s", current_team->name);
            printf("Team %s won the game !\n", current_team->name);
            send_data_to_all_players_from_team(p, current_team, str);
            send_notification_to_gui(myzappy, current_team->name, final_time);
            send_seg_event(p, current_team->name);
            return true;
        }
        current_team = current_team->next;
    }
    return false;
}

bool winning_team(void)
{
    zappy_t *myzappy = (zappy_t *)global_zappy;
    player_info_t *p = myzappy->server->game->players;
    team_info_t *current_team = NULL;
    char *str = NULL;
    time_t end_time = time(NULL);
    double final_time = difftime(end_time, myzappy->server->win_time);

    while (p != NULL) {
        if (p->level >= 8 && notify_winner(p,
            current_team, str, final_time)) {
                printf("Game ended in %f seconds\n", final_time);
                printf("The process time was %f seconds\n",
                    myzappy->server->processor_time);
                return true;
        }
        p = p->next;
    }
    return false;
}
