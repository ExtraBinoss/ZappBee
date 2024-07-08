/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** instructions..h
*/

#pragma once
//msz X Y
//bct X Y q0 q1 q2 q3 q4 q5 q6
//bct X Y q0 q1 q2 q3 q4 q5 q6 * nbr_tiles
//tna N * nbr_teams
//pnw #n X Y O L N
//ppo #n X Y O
//plv #n L
//pin #n q0 q1 q2 q3 q4 q5 q6
//pex #n
//pbc #n M
//pic X Y L #n #n ...
//pie X Y R
//pfk #n
//pdr #n i
//pgt #n i
//pdi #n
//enw #e #n X Y
//ebo #e
//edi #e
//sgt T
//sst T
//seg N
//smg M
//suc
//sbp
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct instruction_s {
    char *msg;
    struct instruction_s *next;
} instruction_t;

typedef struct instruction_info_s {
    const char *name;
    int arg_count;
} instruction_info_t;

typedef struct {
    instruction_t *top;
} instruction_stack_t;

//instructions_list_utils.c
instruction_stack_t *init_instruction(void);
void push_instruction(instruction_stack_t *stack, const char *msg);
void pop_top_instruction(instruction_stack_t *stack);
bool is_instruction_stack_empty(instruction_stack_t *stack);
void free_instructions(instruction_stack_t *stack);
//instructions_parsing.c
void instruction_parsing(instruction_stack_t *stack, char *instruction_set);
//instructions_stack_utils_2.c
char *peek_top_instruction(instruction_stack_t *stack);
