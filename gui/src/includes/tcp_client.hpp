/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** tcp_client
*/

#pragma once

//#include "serv_communication.hpp"

#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <thread>
#include <memory>
#include <deque>
#include <mutex>
#include <sstream>
#include <vector>
#include <queue>

#include "Exceptions.hpp"
#include "zappy_gui.hpp"

namespace zappy
{
    class ZappyGui;

    class TCPClient
    {
    public:
        TCPClient() = default;
        TCPClient(const std::string &ip, int port, zappy::ZappyGui &gui);
        ~TCPClient();
        void initCommandHandlers();
        void selectTcp();
        bool connectToServer();
        std::string getMessages(void) {
            std::lock_guard<std::mutex> lock(_messageQueueMutex); 
            return _messageQueue.front();
        };
        void sendMessage(const std::string &message);
        std::string receiveMessage();
        void closeConnection();
        void executeCommand(std::string commandName, std::string& command);
        void startReadThread(void);
        void startCommandExecutionThread(void);
        void checkAndExecuteCommand(const std::string &word, const std::string& command, std::string& message);
        int getSockfd() const { return _sockfd; };
        fd_set& getReadfds() { return _readfds; };

        void get_mapsize(std::string &command);
        void get_tile_content(std::string &command);
        void get_map_content(std::string &command);
        void get_team_names(std::string &command);
        void get_new_player(std::string &command);
        void get_player_pos(std::string &command);
        void get_player_level(std::string &command);
        void get_player_inventory(std::string &command);
        void get_player_expulsion(std::string &command);
        void get_broadcast(std::string &command);
        void get_incantation_start(std::string &command);
        void get_incantation_end(std::string &command);
        void get_egg_laid_pos(std::string &command);
        void get_egg_laid_player(std::string &command);
        void get_player_drop(std::string &command);
        void get_player_take(std::string &command);
        void get_player_death(std::string &command);
        void get_egg_hatched(std::string &command);
        void get_egg_death(std::string &command);
        void get_time_unit(std::string &command);
        void get_end_game(std::string &command);
        void get_server_message(std::string &command);
        void get_unknown_command(std::string &command);
        void get_bad_parameters(std::string &command);

    private:
        int _height;
        int _select_status;
        struct timeval _timeout;
        //GuiCommands _guiCommands;
        ZappyGui& _gui;
        std::string _server_ip;
        int _server_port;
        int _sockfd;
        fd_set _readfds;
        struct sockaddr_in _server_addr;

        // Circular buffer
        char _buffer[2048];
        int _buffer_head = 0;
        int _buffer_tail = 0;
        using CommandHandler = void (TCPClient::*)(std::string&);
        std::unordered_map<std::string, CommandHandler> _commandHandlers;

        bool bufferIsEmpty() const;
        bool bufferIsFull() const;
        void bufferWrite(char ch);
        std::string bufferReadUntilNewline();
    private:
        //text history
        std::mutex _Textmutex;
        std::string _logText;
        std::deque<std::string> _logHistory;
        std::thread _readThread;
        std::queue<std::string> _messageQueue;
        std::thread _commandExecutionThread;
        std::mutex _messageQueueMutex;
        std::mutex _guiExecutionMutex;
    };
}