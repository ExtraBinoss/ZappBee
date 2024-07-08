/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** network_stack_back
*/

#include "network_stack.h"
#include "network_transactions.h"
#include "garbage_collector.h"

void pop_back(network_stack_t **stack)
{
    network_stack_t *tmp = *stack;
    network_stack_t *prev = NULL;

    if (tmp == NULL)
        return;
    if (tmp->next == NULL) {
        remove_from_garbage(tmp);
        *stack = NULL;
        return;
    }
    while (tmp->next != NULL) {
        prev = tmp;
        tmp = tmp->next;
    }
    remove_from_garbage(tmp);
    prev->next = NULL;
}
