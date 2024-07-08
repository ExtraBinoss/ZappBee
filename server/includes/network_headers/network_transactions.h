/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude [WSL: Ubuntu]
** File description:
** network_transactions
*/

#ifndef NETWORK_TRANSACTIONS_H_
    #define NETWORK_TRANSACTIONS_H_

    #include "network_buffer.h"
    #include "network_stack.h"

bool is_complete(network_buffer_t *buffer);
network_buffer_t *get_buffer(network_stack_t **stack);
bool receive_data(int fd, network_stack_t **stack);
void send_data(int fd, char *data);

#endif /* !NETWORK_TRANSACTIONS_H_ */
