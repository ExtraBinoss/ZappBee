/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** network_buffer
*/

#ifndef NETWORK_BUFFER_H_
    #define NETWORK_BUFFER_H_

    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <stdbool.h>

typedef struct network_buffer_s {
    char *buffer;
    int size;
    int capacity;
    bool completed;
} network_buffer_t;

network_buffer_t *init_buffer(void);
void append_buffer(network_buffer_t *buffer, char *data, int size);
void reset_buffer(network_buffer_t *buffer);
void free_buffer(network_buffer_t *buffer);

    #define BUFFER_SIZE 1024

#endif /* !NETWORK_BUFFER_H_ */
