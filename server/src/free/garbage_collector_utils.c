/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** garbage_collector_utils.c
*/

#include "garbage_collector.h"
#include "zappy.h"

void *new_alloc(size_t size)
{
    void *ptr = malloc(size);

    if (ptr == NULL)
        return NULL;
    add_singleton_garbage(ptr);
    return ptr;
}

void *new_alloc_str(const char *str)
{
    char *ptr = NULL;

    if (str == NULL)
        return NULL;
    ptr = strdup(str);
    if (ptr == NULL)
        return NULL;
    add_singleton_garbage(ptr);
    return ptr;
}

void *new_alloc_calloc(size_t size)
{
    void *ptr = calloc(1, size);

    if (ptr == NULL)
        return NULL;
    add_singleton_garbage(ptr);
    return ptr;
}

int new_alloc_asprintf(char **strp, const char *fmt, ...)
{
    va_list args;
    int result;

    va_start(args, fmt);
    result = vasprintf(strp, fmt, args);
    va_end(args);
    if (result != -1)
        add_singleton_garbage(*strp);
    return result;
}

static void end_server(void)
{
    write(1, "\nServer stopped\n", 16);
    sleep(0.5);
    exit(0);
}

void free_all_garbage_collector(void)
{
    garbage_collector_t *gc = garbage_singleton(NULL);
    garbage_collector_t *next = NULL;

    while (gc != NULL) {
        next = gc->next;
        if (gc->ptr != NULL) {
            free(gc->ptr);
            gc->ptr = NULL;
        }
        if (gc != NULL) {
            free(gc);
            gc = NULL;
        }
        gc = next;
    }
    end_server();
}
