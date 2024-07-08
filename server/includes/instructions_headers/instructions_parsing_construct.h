/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** instructions_parsing_utils.h
*/

#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void construct_instruction(char *instruction, char *token, int arg_count);
bool skip_instructions(char *token);
