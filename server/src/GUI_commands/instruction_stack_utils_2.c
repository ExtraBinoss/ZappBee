/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** instruction_stack_utils_2.c
*/

#include "instructions.h"

char *peek_top_instruction(instruction_stack_t *stack)
{
    if (stack->top == NULL)
        return NULL;
    return stack->top->msg;
}
