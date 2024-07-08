/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** main.c
*/

#include "zappy.h"
#include "garbage_collector.h"

const zappy_t *global_zappy;
bool exit_status;

static void empty_stimeout(zappy_t *zappy)
{
    zappy->server->stimeout.tv_sec = 0;
    zappy->server->stimeout.tv_usec = 0;
}

void signal_handler(int signal)
{
    zappy_t *myzappy = (zappy_t *) global_zappy;

    if (signal == SIGINT) {
        exit_status = true;
        empty_stimeout(myzappy);
    }
    if (signal == SIGQUIT) {
        exit_status = true;
        empty_stimeout(myzappy);
    }
    if (signal == SIGTERM) {
        exit_status = true;
        empty_stimeout(myzappy);
    }
    if (signal == SIGPIPE) {
        return;
    }
}

void catch_signals(void)
{
    signal(SIGINT, signal_handler);
    signal(SIGPIPE, SIG_IGN);
    signal(SIGQUIT, signal_handler);
    signal(SIGTERM, signal_handler);
}

void server_connection_init(zappy_t *zappy)
{
    zappy->server->sock_ad.sin_port = htons(zappy->server->port);
    zappy->server->sock_ad.sin_family = AF_INET;
    zappy->server->sock_ad.sin_addr.s_addr = INADDR_ANY;
    zappy->server->sock_len = sizeof(struct sockaddr_in);
}

void check_args(int argc, char const **argv, zappy_t *zappy)
{
    int flag_found = 0;

    init_all_struct(zappy);
    if (argc < 13) {
        fprintf(stderr, "Usage: ./zappy_server -p port -x width -y height \
        -n name1 name2 ... -c clientsNb -f freq\n");
        exit(84);
    }
    for (int i = 1; i < argc; i++) {
        flag_found = 0;
        parsing_args(&i, argc, argv, &flag_found);
    }
    if (!flag_found) {
        fprintf(stderr, "Usage: ./zappy_server -p port -x width -y height"
        "-n name1 name2 ... -c clientsNb -f freq\n");
        exit(84);
    }
    server_connection_init(zappy);
    argument_logs();
}

int main(int argc, char const **argv)
{
    zappy_t zappy;
    garbage_collector_t *gc = create_garbage_collector();

    exit_status = false;
    garbage_singleton(gc);
    global_zappy = &zappy;
    check_args(argc, argv, &zappy);
    server_setup(&zappy);
    generate_map();
    set_teams_spawnpoints(&zappy);
    catch_signals();
    zappy_loop(&zappy);
    return 0;
}
