/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** execute_look.c
*/

#include "execute_commands.h"

static void smart_strcat(char **dest, char *src)
{
    size_t dest_len = *dest ? strlen(*dest) : 0;
    size_t src_len = strlen(src);

    *dest = new_realloc_str(*dest, dest_len + src_len + 1);
    strncat(*dest + dest_len, src, src_len);
    (*dest)[dest_len + src_len] = '\0';
}

static int get_circ_coord(int i, int max)
{
    if (i >= 0 && i < max)
        return i;
    if (i >= max)
        return get_circ_coord(0 + (i - max), max);
    if (i < 0)
        return get_circ_coord(max - i, max);
    return 0;
}

static int get_number_of_players_on_tile(tile_t *tile)
{
    zappy_t *z = (zappy_t *) global_zappy;
    int players = 0;

    for (player_info_t *p = z->server->game->players; p != NULL; p = p->next)
        if ((size_t) p->x == tile->x && (size_t) p->y == tile->y)
            players++;
    return players;
}

// algorithme qui va ajouter à la string la ressource donnée en argument
// id -> 0 = food, 1 = linemate, 2 = deraumere, 3 = sibur, 4 = mendiane,
// 5 = phiras, 6 = thystame, 7 = player
static void add_content_to_buffer(int id, int quantity, char **buffer)
{
    for (int i = 0; i < quantity; i++) {
        if (id == 0)
            smart_strcat(buffer, " food\0");
        if (id == 1)
            smart_strcat(buffer, " linemate\0");
        if (id == 2)
            smart_strcat(buffer, " deraumere\0");
        if (id == 3)
            smart_strcat(buffer, " sibur\0");
        if (id == 4)
            smart_strcat(buffer, " mendiane\0");
        if (id == 5)
            smart_strcat(buffer, " phiras\0");
        if (id == 6)
            smart_strcat(buffer, " thystame\0");
        if (id == 7)
            smart_strcat(buffer, " player\0");
    }
}

// algorithme qui va ajouter à la string les ressources de la tile
// donnée en argument
static void add_tile_res_to_buffer(tile_t *tile, char **buffer)
{
    add_content_to_buffer(7, get_number_of_players_on_tile(tile), buffer);
    add_content_to_buffer(0, tile->tile_ressources->food, buffer);
    add_content_to_buffer(1, tile->tile_ressources->linemate, buffer);
    add_content_to_buffer(2, tile->tile_ressources->deraumere, buffer);
    add_content_to_buffer(3, tile->tile_ressources->sibur, buffer);
    add_content_to_buffer(4, tile->tile_ressources->mendiane, buffer);
    add_content_to_buffer(5, tile->tile_ressources->phiras, buffer);
    add_content_to_buffer(6, tile->tile_ressources->thystame, buffer);
}

// algorithme qui génère et malloc la string pour le joueur qui
// regarde vers le haut pour la return
char *look_up(int vision_range, int x, int y)
{
    char *data = new_alloc_calloc(sizeof(char) * 10 + 1);
    tile_t *h = global_zappy->server->map->tiles;
    int truex = 0;
    int truey = 0;

    smart_strcat(&data, "[\0");
    add_tile_res_to_buffer(find_tile_by_pos(h, x, y), &data);
    for (int v = 1; v < vision_range; v++) {
        for (int i = -v; i <= v; i++) {
            truex = get_circ_coord(x + i, global_zappy->server->game->width);
            truey = get_circ_coord(y + v, global_zappy->server->game->height);
            smart_strcat(&data, ",\0");
            add_tile_res_to_buffer(find_tile_by_pos(h, truex, truey), &data);
        }
    }
    smart_strcat(&data, "]\n\0");
    return data;
}

// algorithme qui génère et malloc la string pour le joueur qui
// regarde vers le bas pour la return
char *look_down(int vision_range, int x, int y)
{
    char *data = new_alloc_calloc(sizeof(char) * 10 + 1);
    tile_t *h = global_zappy->server->map->tiles;
    int truex = 0;
    int truey = 0;

    smart_strcat(&data, "[\0");
    add_tile_res_to_buffer(find_tile_by_pos(h, x, y), &data);
    for (int v = 1; v < vision_range; v++) {
        for (int i = v; i >= -v; i--) {
            truex = get_circ_coord(x + i, global_zappy->server->game->width);
            truey = get_circ_coord(y - v, global_zappy->server->game->height);
            smart_strcat(&data, ",\0");
            add_tile_res_to_buffer(find_tile_by_pos(h, truex, truey), &data);
        }
    }
    smart_strcat(&data, "]\n\0");
    return data;
}

// algorithme qui génère et malloc la string pour le joueur qui
// regarde vers la gauche pour la return
char *look_left(int vision_range, int x, int y)
{
    char *data = new_alloc_calloc(sizeof(char) * 10 + 1);
    tile_t *h = global_zappy->server->map->tiles;
    int truex = 0;
    int truey = 0;

    smart_strcat(&data, "[\0");
    add_tile_res_to_buffer(find_tile_by_pos(h, x, y), &data);
    for (int v = 1; v < vision_range; v++) {
        for (int i = -v; i <= v; i++) {
            truex = get_circ_coord(x - v, global_zappy->server->game->width);
            truey = get_circ_coord(y + i, global_zappy->server->game->height);
            smart_strcat(&data, ",\0");
            add_tile_res_to_buffer(find_tile_by_pos(h, truex, truey), &data);
        }
    }
    smart_strcat(&data, "]\n\0");
    return data;
}

// algorithme qui génère et malloc la string pour le joueur qui
// regarde vers la droite pour la return
char *look_right(int vision_range, int x, int y)
{
    char *data = new_alloc_calloc(sizeof(char) * 10 + 1);
    tile_t *h = global_zappy->server->map->tiles;
    int truex = 0;
    int truey = 0;

    smart_strcat(&data, "[\0");
    add_tile_res_to_buffer(find_tile_by_pos(h, x, y), &data);
    for (int v = 1; v < vision_range; v++) {
        for (int i = v; i >= -v; i--) {
            truex = get_circ_coord(x + v, global_zappy->server->game->width);
            truey = get_circ_coord(y + i, global_zappy->server->game->height);
            smart_strcat(&data, ",\0");
            add_tile_res_to_buffer(find_tile_by_pos(h, truex, truey), &data);
        }
    }
    smart_strcat(&data, "]\n\0");
    return data;
}

void execute_look_command(player_info_t *player, char *arg)
{
    int vision_range = player->level + 1;
    char *data = NULL;

    (void)arg;
    if (player->timer_action <= 0) {
        if (player->direction == UP)
            data = look_up(vision_range, player->x, player->y);
        if (player->direction == DOWN)
            data = look_down(vision_range, player->x, player->y);
        if (player->direction == LEFT)
            data = look_left(vision_range, player->x, player->y);
        if (player->direction == RIGHT)
            data = look_right(vision_range, player->x, player->y);
        if (data != NULL) {
            send_data(player->fd, data);
            remove_from_garbage(data);
        }
        log_message("log/look.log", GREEN, "[%d] Look OK\n", player->fd);
    }
}
