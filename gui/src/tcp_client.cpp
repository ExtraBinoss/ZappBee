/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** tcp_client
*/

#include "includes/tcp_client.hpp"
namespace zappy
{
    void TCPClient::initCommandHandlers()
    {
        _commandHandlers["msz"] = &TCPClient::get_mapsize;
        _commandHandlers["bct"] = &TCPClient::get_tile_content;
        _commandHandlers["tna"] = &TCPClient::get_team_names;
        _commandHandlers["pnw"] = &TCPClient::get_new_player;
        _commandHandlers["ppo"] = &TCPClient::get_player_pos;
        _commandHandlers["plv"] = &TCPClient::get_player_level;
        _commandHandlers["pin"] = &TCPClient::get_player_inventory;
        _commandHandlers["pex"] = &TCPClient::get_player_expulsion;
        _commandHandlers["pbc"] = &TCPClient::get_broadcast;
        _commandHandlers["pic"] = &TCPClient::get_incantation_start;
        _commandHandlers["pie"] = &TCPClient::get_incantation_end;
        _commandHandlers["pfk"] = &TCPClient::get_egg_laid_player;
        _commandHandlers["pdr"] = &TCPClient::get_player_drop;
        _commandHandlers["pgt"] = &TCPClient::get_player_take;
        _commandHandlers["pdi"] = &TCPClient::get_player_death;
        _commandHandlers["enw"] = &TCPClient::get_egg_laid_pos;
        _commandHandlers["eht"] = &TCPClient::get_egg_hatched;
        _commandHandlers["ebo"] = &TCPClient::get_egg_death;
        _commandHandlers["edi"] = &TCPClient::get_egg_death;
        _commandHandlers["sgt"] = &TCPClient::get_time_unit;
        _commandHandlers["sst"] = &TCPClient::get_time_unit;
        _commandHandlers["seg"] = &TCPClient::get_end_game;
        _commandHandlers["smg"] = &TCPClient::get_server_message;
        _commandHandlers["suc"] = &TCPClient::get_unknown_command;
        _commandHandlers["sbp"] = &TCPClient::get_bad_parameters;
    }
    TCPClient::TCPClient(const std::string &ip, int port, zappy::ZappyGui &gui) : _gui(gui), _server_ip(ip), _server_port(port), _sockfd(-1)
    {
        std::cout << "Creating TCP client : " << ip << ":" << port << std::endl;
        memset(&_server_addr, 0, sizeof(_server_addr));
        _server_addr.sin_family = AF_INET;
        _server_addr.sin_port = htons(_server_port);
        if (!connectToServer())
            exit(3);
        std::string receivedMessage = receiveMessage();
        if (receivedMessage.find("WELCOME") == std::string::npos) {
            exit(4);
        } else {
            sendMessage("GRAPHIC");
        }
        _select_status = 0;
        _timeout = {0, 5000};

        initCommandHandlers();
        startReadThread();
        startCommandExecutionThread();
    }

    void TCPClient::checkAndExecuteCommand(const std::string &word, const std::string& command, std::string& message) {
        if (word.find(command) != std::string::npos) {
            executeCommand(command, message);
        }
    }
    void TCPClient::startCommandExecutionThread(void)
    {
        _commandExecutionThread = std::thread([&]() {
            while (true) {
                if (!_messageQueue.empty()) {
                    {
                        std::lock_guard<std::mutex> lock(_messageQueueMutex);
                        std::string message = _messageQueue.front();
                        _messageQueue.pop();

                    std::vector<std::string> commands = {"sgt", "sst", "ppo", "plv", "pin", "msz", "bct", "mct", "tna", "pnw", "pex", "pbc", "pic", "pie", "pfk", "pdr", "pgt", "pdi", "enw", "eht", "ebo", "edi", "seg", "smg", "suc", "sbp"};
                    message.erase(std::remove(message.begin(), message.end(), '\n'), message.end());
                    std::istringstream iss(message);
                    std::cout << "command: [" << message << "]" << std::endl;
                    std::string word;
                    while (iss >> word) {
                        for (const auto &command : commands) {
                            checkAndExecuteCommand(word, command, message);
                        }
                    }
                    }

                }
            }
        });
    }

    void TCPClient::startReadThread(void)
    {
        _readThread = std::thread([&]() {
        while (true) {
            std::string receivedMessage = receiveMessage();
            if (receivedMessage.empty())
                return;
            {
                std::lock_guard<std::mutex> lock(_messageQueueMutex);
                _messageQueue.push(receivedMessage);
            }
        }});
    }

    TCPClient::~TCPClient()
    { 
        std::cout << "Closing TCP client" << std::endl;
        if (_readThread.joinable())
            _readThread.join();
        if (_commandExecutionThread.joinable())
            _commandExecutionThread.join();
        closeConnection();
    }

    void TCPClient::executeCommand(std::string commandName, std::string& command)
    {
        auto it = _commandHandlers.find(commandName);
        if (it != _commandHandlers.end()) {
            (this->*(it->second))(command);
        }
    }

    void TCPClient::selectTcp()
    {
        if (_sockfd < 0) {
            throw TCPException("Error: Socket is under 0");
        }
        FD_ZERO(&_readfds);
        FD_SET(_sockfd, &_readfds);
        _select_status = select(_sockfd + 1, &_readfds, NULL, NULL, &_timeout);
        if (_select_status < 0) {
            throw TCPException("Error: Select failed");
        }
    }

    bool TCPClient::connectToServer()
    {
        // Convert IP address to binary form
        if (inet_pton(AF_INET, _server_ip.c_str(), &_server_addr.sin_addr) <= 0)
        {
            std::cerr << "Error: Invalid address | " << _server_ip.c_str() << std::endl;
            return false;
        }

        // Create socket
        _sockfd = socket(AF_INET, SOCK_STREAM, 0);
        std::cout << "Socket created" << _sockfd << std::endl;
        if (_sockfd < 0)
        {
            throw TCPException("Error: Socket creation failed");
            return false;
        }

        // Connect to the server
        if (connect(_sockfd, (struct sockaddr *)&_server_addr, sizeof(_server_addr)) < 0)
        {
            std::cerr << "Error: Connection failed" << std::endl;
            close(_sockfd);
            return false;
        }

        std::cout << "Connected to the server" << std::endl;
        return true;
    }

    void TCPClient::sendMessage(const std::string &message)
    {
        if (_sockfd < 0)
        {
            throw TCPException("Error: Socket not initialized");
            return;
        }
        send(_sockfd, message.c_str(), message.length(), 0);
    }

    static void set_fd_non_blocking(int fd) {
        int flags = fcntl(fd, F_GETFL, 0);

        if (flags == -1) {
            return;
        }
        flags |= O_NONBLOCK;
        fcntl(fd, F_SETFL, flags);
    }

    static void set_fd_blocking(int fd) {
        int flags = fcntl(fd, F_GETFL, 0);

        if (flags == -1) {
            return;
        }
        flags &= ~O_NONBLOCK;
        fcntl(fd, F_SETFL, flags);
    }

    std::string TCPClient::receiveMessage()
    {
        if (_sockfd < 0)
        {
            std::cerr << "Error: Socket not initialized" << std::endl;
            return "";
        }
        std::vector<char> buffer(1024);
        std::fill(buffer.begin(), buffer.end(), 0);
        char temp_buffer[2] = {0};
        int bytes_read = read(_sockfd, temp_buffer, 1);
        set_fd_non_blocking(_sockfd);
        if (bytes_read <= 0)
            return "";
        while (bytes_read > 0) {
            std::copy(temp_buffer, temp_buffer + bytes_read, std::back_inserter(buffer));
            if (temp_buffer[0] == '\n') {
                break;
            }
            bytes_read = read(_sockfd, temp_buffer, 1);
            if (bytes_read <= 0)
                break;
        }
        set_fd_blocking(_sockfd);
        std::string message(buffer.begin(), buffer.end());
        return message;
    }

    void TCPClient::closeConnection()
    {
        if (_sockfd >= 0)
        {
            close(_sockfd);
            _sockfd = -1;
        }
        exit(0);
    }

    bool TCPClient::bufferIsEmpty() const
    {
        return _buffer_head == _buffer_tail;
    }

    bool TCPClient::bufferIsFull() const
    {
        return (_buffer_head + 1) % sizeof(_buffer) == static_cast<size_t>(_buffer_tail);
    }

    void TCPClient::bufferWrite(char ch)
    {
        if (!bufferIsFull())
        {
            _buffer[_buffer_head] = ch;
            _buffer_head = (_buffer_head + 1) % sizeof(_buffer);
        }
    }

    std::string TCPClient::bufferReadUntilNewline()
    {
        std::string message;
        int temp_tail = _buffer_tail;

        while (temp_tail != _buffer_head)
        {
            char ch = _buffer[temp_tail];
            message += ch;
            temp_tail = (temp_tail + 1) % 1024;
            if (ch == '\n')
            {
                _buffer_tail = temp_tail;
                return message;
            }
        }

        return "";
    }
}
