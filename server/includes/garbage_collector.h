/*
** EPITECH PROJECT, 2023
** B-NWP-400-MPL-4-1-myftp-alan.trebugeais
** File description:
** garbage_collector.h
*/

#pragma once
#define _GNU_SOURCE // for new_alloc_asprintf
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

typedef struct garbage_collector_s {
    void *ptr;
    struct garbage_collector_s *next;
} garbage_collector_t;

void *garbage_singleton(void *ptr);
garbage_collector_t *create_garbage_collector(void);
void add_singleton_garbage(void *ptr);
void *new_alloc(size_t size);
void *new_alloc_str(const char *str);
void *new_alloc_calloc(size_t size);
void *new_realloc_str(void *ptr, size_t size);
void remove_from_garbage(void *ptr);
int new_alloc_asprintf(char **strp, const char *fmt, ...);
void free_all_garbage_collector(void);
