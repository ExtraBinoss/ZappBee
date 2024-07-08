/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** general_utils.c
*/

#include "general_utils.h"
#include "garbage_collector.h"

char *malloc_check(size_t size)
{
    char *ptr = new_alloc(size);

    if (ptr == NULL) {
        perror("malloc");
        exit(84);
    }
    return ptr;
}
