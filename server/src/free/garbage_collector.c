/*
** EPITECH PROJECT, 2023
** B-NWP-400-MPL-4-1-myftp-alan.trebugeais
** File description:
** garbage_collector_func.c
*/

#include "garbage_collector.h"
#include <string.h>

garbage_collector_t *create_garbage_collector(void)
{
    garbage_collector_t *gc = malloc(sizeof(garbage_collector_t));

    gc->ptr = NULL;
    gc->next = NULL;
    return gc;
}

void *garbage_singleton(void *ptr)
{
    static garbage_collector_t *gc = NULL;

    if (ptr != NULL) {
        gc = ptr;
    }
    return gc;
}

void add_singleton_garbage(void *ptr)
{
    garbage_collector_t *gc = garbage_singleton(NULL);
    garbage_collector_t *new_gc = malloc(sizeof(garbage_collector_t));

    new_gc->ptr = ptr;
    new_gc->next = gc;
    garbage_singleton(new_gc);
}

static void free_both_pointers(garbage_collector_t **gc)
{
    if ((*gc)->ptr != NULL) {
        free((*gc)->ptr);
        (*gc)->ptr = NULL;
    }
    if (*gc != NULL) {
        free(*gc);
        *gc = NULL;
    }
}

void remove_from_garbage(void *ptr)
{
    garbage_collector_t *gc = garbage_singleton(NULL);
    garbage_collector_t *tmp = gc;
    garbage_collector_t *prev = NULL;

    if (gc == NULL)
        return;
    if (gc->ptr == ptr) {
        gc = gc->next;
        garbage_singleton(gc);
        free_both_pointers(&tmp);
        return;
    }
    while (tmp != NULL && tmp->ptr != ptr) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;
    prev->next = tmp->next;
    free_both_pointers(&tmp);
}
