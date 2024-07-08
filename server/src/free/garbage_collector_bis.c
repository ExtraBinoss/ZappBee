/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** garbage_collector_bis.c
*/

#include "garbage_collector.h"

void *new_realloc_str(void *ptr, size_t size)
{
    void *new_ptr = malloc(size);

    if (new_ptr == NULL) {
        free(ptr);
        return NULL;
    }
    memcpy(new_ptr, ptr, strlen(ptr) + 1);
    remove_from_garbage(ptr);
    add_singleton_garbage(new_ptr);
    return new_ptr;
}
