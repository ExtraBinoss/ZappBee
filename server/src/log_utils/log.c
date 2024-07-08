/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** log.c
*/

#include "log.h"

const char *color_codes[] = {
    "\x1b[31m",
    "\x1b[32m",
    "\x1b[33m",
    "\x1b[34m",
    "\x1b[35m",
    "\x1b[36m",
    "\x1b[0m"
};

void log_message(const char *filename, color_t color, const char *format, ...)
{
    FILE *file = fopen(filename, "a");
    va_list args;

    if (file == NULL || filename == NULL || format == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return;
    }
    va_start(args, format);
    fprintf(file, "%s", color_codes[color]);
    vfprintf(file, format, args);
    fprintf(file, "%s", color_codes[RESET]);
    va_end(args);
    fclose(file);
}

void argument_logs(void)
{
    zappy_t *zappy = (zappy_t *) global_zappy;

    log_message("log/zappy_server_parser.log", GREEN, "port: %d\n",
        zappy->server->port);
    log_message("log/zappy_server_parser.log", GREEN, "width: %d\n",
        zappy->server->game->width);
    log_message("log/zappy_server_parser.log", GREEN, "height: %d\n",
        zappy->server->game->height);
    log_message("log/zappy_server_parser.log", GREEN, "clientsNb: %d\n",
        zappy->server->game->clientsNb);
    log_message("log/zappy_server_parser.log", GREEN, "freq: %d\n",
        zappy->server->game->freq);
    for (team_info_t *tmp = zappy->server->game->teams; tmp; tmp = tmp->next) {
        if (tmp->name == NULL)
            return;
        log_message("log/zappy_server_parser.log", GREEN,
            "team: %s, slotsAvailable: %d\n", tmp->name, tmp->slotAvailable);
    }
}
