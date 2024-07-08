/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** help
*/

#include "utils/help.hpp"

void print_help(void)
{
    std::cout << "USAGE: ./zappy_gui -p port [-h host]" << std::endl;
    std::cout << "\t-p port\tis the port number" << std::endl;
    std::cout << "\t-h host\tis the name of the machine; localhost by default" << std::endl;
    exit(0);
}
