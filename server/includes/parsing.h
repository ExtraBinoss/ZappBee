/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** parsing.h
*/

#pragma once

#include "zappy.h"

typedef struct zappy_s zappy_t;

//handle p,x,y,n,c,f arguments are static functions in parsing.c
void parsing_args(int *i, int argc, char const **argv, int *flag_found);
