/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** parsing.c
*/

#include "parsing.h"

static void handle_p_arg(int *i, int argc, char const **argv, int *flag_found)
{
    zappy_t *myzappy = (zappy_t *) global_zappy;

    if (strcmp(argv[*i], "-p") == 0 && *i + 1 < argc) {
        myzappy->server->port = atoi(argv[*i + 1]);
        if (myzappy->server->port < 1024 || myzappy->server->port > 65535) {
            fprintf(stderr, "Port must be between 1024 and 65535\n");
            exit(84);
        }
        *i += 1;
        *flag_found = 1;
    }
}

static void handle_x_arg(int *i, int argc, char const **argv, int *flag_found)
{
    zappy_t *myzappy = (zappy_t *) global_zappy;

    if (strcmp(argv[*i], "-x") == 0 && *i + 1 < argc) {
        myzappy->server->game->width = atoi(argv[*i + 1]);
        *i += 1;
        *flag_found = 1;
    }
}

static void handle_y_arg(int *i, int argc, char const **argv, int *flag_found)
{
    zappy_t *myzappy = (zappy_t *) global_zappy;

    if (strcmp(argv[*i], "-y") == 0 && *i + 1 < argc) {
        myzappy->server->game->height = atoi(argv[*i + 1]);
        *i += 1;
        *flag_found = 1;
    }
}

void create_teams(int *j, int argc, char const **argv, zappy_t *myzappy)
{
    team_info_t *new_team = NULL;
    int ID = 1;

    for (; *j < argc; (*j)++) {
        if (strcmp(argv[*j], "-c") == 0)
            break;
        new_team = new_alloc(sizeof(team_info_t));
        new_team->name = new_alloc_str(argv[*j]);
        new_team->ID = ID;
        new_team->slotAvailable = 0;
        new_team->slotMax = 0;
        new_team->spawnpoint_x = 0;
        new_team->spawnpoint_y = 0;
        new_team->eggs = NULL;
        new_team->next = myzappy->server->game->teams;
        myzappy->server->game->teams = new_team;
        ID++;
    }
    myzappy->server->game->team_max_id = ID - 1;
}

static void handle_n_arg(int *i, int argc, char const **argv, int *flag_found)
{
    zappy_t *myzappy = (zappy_t *) global_zappy;
    int j = 0;

    if (strcmp(argv[*i], "-n") == 0 && *i + 1 < argc) {
        j = *i + 1;
        create_teams(&j, argc, argv, myzappy);
        *i = j - 1;
        *flag_found = 1;
    }
}

static void handle_c_arg(int *i, int argc, char const **argv, int *flag_found)
{
    zappy_t *myzappy = (zappy_t *) global_zappy;

    if (strcmp(argv[*i], "-c") == 0 && *i + 1 < argc) {
        myzappy->server->game->clientsNb = atoi(argv[*i + 1]);
        *i += 1;
        *flag_found = 1;
    }
}

static void handle_f_arg(int *i, int argc, char const **argv, int *flag_found)
{
    zappy_t *myzappy = (zappy_t *) global_zappy;

    if (strcmp(argv[*i], "-f") == 0 && *i + 1 < argc) {
        myzappy->server->game->freq = atof(argv[*i + 1]);
        *i += 1;
        *flag_found = 1;
    }
}

void parsing_args(int *i, int argc, char const **argv, int *flag_found)
{
    zappy_t *myzappy = (zappy_t *) global_zappy;

    handle_p_arg(i, argc, argv, flag_found);
    handle_x_arg(i, argc, argv, flag_found);
    handle_y_arg(i, argc, argv, flag_found);
    handle_n_arg(i, argc, argv, flag_found);
    handle_c_arg(i, argc, argv, flag_found);
    handle_f_arg(i, argc, argv, flag_found);
    if (myzappy->server->game->clientsNb != 0)
        for (team_info_t *tmp = myzappy->server->game->teams;
            tmp; tmp = tmp->next) {
                tmp->slotAvailable = myzappy->server->game->clientsNb;
                tmp->slotMax = myzappy->server->game->clientsNb;
            }
}
