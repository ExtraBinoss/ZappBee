/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude [WSL: Ubuntu]
** File description:
** network_stack
*/

#include "network_stack.h"
#include "network_transactions.h"
#include "garbage_collector.h"

void push_back(network_stack_t **stack, network_buffer_t *buffer)
{
    network_stack_t *new_node = new_alloc(sizeof(network_stack_t));
    network_stack_t *current;

    new_node->buffer = buffer;
    new_node->next = NULL;
    if (*stack == NULL) {
        *stack = new_node;
    } else {
        current = *stack;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}

void pop_top(network_stack_t **stack)
{
    network_stack_t *tmp = *stack;
    network_buffer_t *buffer = NULL;

    if (tmp) {
        *stack = tmp->next;
        buffer = tmp->buffer;
        if (buffer != NULL)
            remove_from_garbage(buffer);
        if (tmp != NULL)
            remove_from_garbage(tmp);
    }
}

char *peek_top(network_stack_t *stack)
{
    if (stack && stack->buffer && stack->buffer->completed) {
        return stack->buffer->buffer;
    }
    return NULL;
}

void free_stack(network_stack_t *stack)
{
    network_stack_t *tmp = stack;

    while (stack) {
        tmp = stack;
        stack = stack->next;
        remove_from_garbage(tmp->buffer);
        remove_from_garbage(tmp);
    }
}

int stack_size(network_stack_t *stack)
{
    int size = 0;

    while (stack) {
        size++;
        stack = stack->next;
    }
    return size;
}
