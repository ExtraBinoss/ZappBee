/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude [WSL: Ubuntu]
** File description:
** network_buffer
*/

#include "network_buffer.h"
#include "garbage_collector.h"

network_buffer_t *init_buffer(void)
{
    network_buffer_t *buffer = new_alloc(sizeof(network_buffer_t));

    buffer->buffer = new_alloc(sizeof(char) * BUFFER_SIZE);
    buffer->size = 0;
    buffer->capacity = BUFFER_SIZE;
    buffer->completed = false;
    return buffer;
}

void append_buffer(network_buffer_t *buffer, char *data, int size)
{
    if (buffer->size + size >= buffer->capacity) {
        buffer->capacity *= 2;
        buffer->buffer = new_realloc_str(buffer->buffer, buffer->capacity);
    }
    memcpy(buffer->buffer + buffer->size, data, size);
    buffer->size += size;
    buffer->buffer[buffer->size] = '\0';
}

void reset_buffer(network_buffer_t *buffer)
{
    buffer->size = 0;
    buffer->completed = false;
}

void free_buffer(network_buffer_t *buffer)
{
    if (buffer != NULL && buffer->buffer != NULL) {
        remove_from_garbage(buffer->buffer);
    }
    if (buffer != NULL) {
        remove_from_garbage(buffer);
    }
    buffer = NULL;
}
