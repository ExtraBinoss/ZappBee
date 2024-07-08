/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** main
*/

#include "utils/help.hpp"
#include "zappy_gui.hpp"
#include "Exceptions.hpp"

zappy::TCPClient init(int ac, char const **av, zappy::ZappyGui &gui)
{
    std::vector<std::string> args(av, av + ac);
    auto it_port = std::find(args.begin(), args.end(), "-p");
    auto it_host = std::find(args.begin(), args.end(), "-h");

    if (it_port == args.end() || it_host == args.end() || 
        ++it_port == args.end() || ++it_host == args.end()) {
            exit(1);
    }

    int port = std::stoi(*it_port);
    std::string host = *it_host;
    return zappy::TCPClient(host, port, gui);
}

int main(int ac, char const **av)
{
    zappy::ZappyGui gui;
    
    zappy::TCPClient tcp = init(ac, av, gui);
    if (!gui.init()) {
        std::cerr << "Error: Could not initialize the GUI" << std::endl;
        print_help();
        return 84;
    }
    try {
        gui.run(tcp);
    } catch (const zappy::ZappyException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
