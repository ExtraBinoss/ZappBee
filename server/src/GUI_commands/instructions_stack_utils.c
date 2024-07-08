/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** instructions.c
*/

#include "instructions.h"
#include "garbage_collector.h"

instruction_stack_t *init_instruction(void)
{
    instruction_stack_t *stack = new_alloc(sizeof(instruction_stack_t));

    stack->top = NULL;
    return stack;
}

void push_instruction(instruction_stack_t *stack, const char *msg)
{
    instruction_t *new_instruction = new_alloc(sizeof(instruction_t));

    new_instruction->msg = new_alloc_str(msg);
    new_instruction->next = stack->top;
    stack->top = new_instruction;
}

void pop_top_instruction(instruction_stack_t *stack)
{
    instruction_t *tmp = stack->top;

    if (tmp) {
        stack->top = tmp->next;
        remove_from_garbage(tmp->msg);
        remove_from_garbage(tmp);
    }
}

bool is_instruction_stack_empty(instruction_stack_t *stack)
{
    return stack->top == NULL;
}

void free_instructions(instruction_stack_t *stack)
{
    instruction_t *current = stack->top;
    instruction_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        remove_from_garbage(current->msg);
        remove_from_garbage(current);
        current = next;
    }
    stack->top = NULL;
}
