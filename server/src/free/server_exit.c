/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** server_exit
*/

#include "zappy.h"

/**
 * @brief Frees the resources allocated for the Zappy server.
 *
 * This function closes the file descriptor associated with the server.
 * free map (free map and all tiles)
 * free game (free game struct and all teams)
 *
 * @param zappy The Zappy server instance.
 */
void zappy_free(const zappy_t *zappy)
{
    free_map(zappy->server->map);
    free_game(zappy->server->game);
    close(zappy->server->fd);
    free(zappy->server);
    free(zappy->gui);
    free(zappy->IA);
}

void exit_cleanly(void)
{
    free_all_garbage_collector();
    exit(0);
}

void exit_error(char *msg)
{
    log_message("log/exit_error.log", RED, msg);
    free_all_garbage_collector();
    exit(84);
}
