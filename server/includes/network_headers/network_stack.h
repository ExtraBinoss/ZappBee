/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude [WSL: Ubuntu]
** File description:
** network_stack
*/

#ifndef NETWORK_STACK_H_
    #define NETWORK_STACK_H_

    #include "network_buffer.h"

typedef struct network_stack_s {
    network_buffer_t *buffer;
    struct network_stack_s *next;
} network_stack_t;

void push_back(network_stack_t **stack, network_buffer_t *buffer);
void pop_top(network_stack_t **stack);
void pop_back(network_stack_t **stack);
char *peek_top(network_stack_t *stack);
void free_stack(network_stack_t *stack);
int stack_size(network_stack_t *stack);

#endif /* !NETWORK_STACK_H_ */
