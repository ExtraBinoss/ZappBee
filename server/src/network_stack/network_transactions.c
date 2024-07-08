/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude [WSL: Ubuntu]
** File description:
** network_transactions
*/

#include "network_transactions.h"
#include <stdio.h>
#include "log.h"
#include <fcntl.h>

bool is_complete(network_buffer_t *buffer)
{
    bool completed = false;

    if (buffer != NULL && buffer->buffer != NULL &&
        buffer->size > 0 && buffer->buffer[buffer->size - 1] == '\n') {
        completed = true;
    }
    buffer->completed = completed;
    return completed;
}

network_buffer_t *get_buffer(network_stack_t **stack)
{
    network_buffer_t *buffer = NULL;

    if (*stack == NULL || is_complete((*stack)->buffer)) {
        buffer = init_buffer();
    } else {
        while ((*stack)->next != NULL) {
            stack = &(*stack)->next;
        }
        buffer = (*stack)->buffer;
    }
    return buffer;
}

static void set_fd_blocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);

    if (flags == -1) {
        log_message("log/network_transactions.log", RED,
        "Error: fcntl failed\n");
        return;
    }
    flags &= ~O_NONBLOCK;
    fcntl(fd, F_SETFL, flags);
}

static void set_fd_non_blocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);

    if (flags == -1) {
        log_message("log/network_transactions.log", RED,
        "Error: fcntl failed\n");
        return;
    }
    flags |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flags);
}

bool process_data(int fd, network_stack_t **stack, network_buffer_t *buffer)
{
    char temp[2] = {0};
    ssize_t bytes = read(fd, temp, 1);

    set_fd_non_blocking(fd);
    if (bytes <= 0)
        return false;
    while (bytes > 0) {
        append_buffer(buffer, temp, bytes);
        if (temp[0] == '\n') {
            buffer->completed = true;
            push_back(stack, buffer);
            break;
        }
        bytes = read(fd, temp, 1);
        if (bytes <= 0)
            break;
    }
    set_fd_blocking(fd);
    return true;
}

bool receive_data(int fd, network_stack_t **stack)
{
    network_buffer_t *buffer = get_buffer(stack);
    bool status = process_data(fd, stack, buffer);

    if (status == false) {
        free_buffer(buffer);
        return false;
    }
    return true;
}

void send_data(int fd, char *data)
{
    if (fd == -1 || data == NULL) {
        log_message("log/send_data.log", RED, "FD : %d\n", fd);
        log_message("log/send_data.log", RED, "Error: fd or data is NULL,",
        "data : %d\n", data);
        return;
    }
    write(fd, data, strlen(data));
    printf("[%d] Data sent: %s\n", fd, data);
}
