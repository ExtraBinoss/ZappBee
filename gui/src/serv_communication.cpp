/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** serv_communication.cpp
*/

#include "tcp_client.hpp"
#include <iostream>
#include <sstream>
#include "SFML/Graphics.hpp"

//msz x y
void zappy::TCPClient::get_mapsize(std::string &command)
{
    std::istringstream iss(command);
    std::string cmd;
    int x, y;

    if (!(iss >> cmd >> x >> y)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
    std::cout << "Map size: " << x << " " << y << std::endl;
    {
        std::lock_guard<std::mutex> lock(_guiExecutionMutex);
        _height = y - 1;
        _gui.initMap(x, y);
        std::cout << "Map initialized" << std::endl;
    }
}

//bct x y q0 q1 q2 q3 q4 q5 q6
void zappy::TCPClient::get_tile_content(std::string &command)
{
    std::istringstream iss(command);
    std::string cmd;
    int X, Y, q0, q1, q2, q3, q4, q5, q6;

    if (!(iss >> cmd >> X >> Y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
    {
        std::lock_guard<std::mutex> lock(_guiExecutionMutex);
        _gui.setTileContent(sf::Vector2i(X, _height - Y), {q0, q1, q2, q3, q4, q5, q6});
    }
}

//tna team_name
void zappy::TCPClient::get_team_names(std::string &command)
{
    std::istringstream iss(command);
    std::string cmd;
    std::string team_name;
    std::vector<std::string> teams;

    std::cout << "Team name: " << command << std::endl;

    if (!(iss >> cmd >> team_name)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
    {
        std::lock_guard<std::mutex> lock(_guiExecutionMutex);
        _gui.addTeam(team_name);
        _gui.initInfos();
    }
}

//pnw #n X Y O L N
void zappy::TCPClient::get_new_player(std::string &command)
{
    command.erase(std::remove(command.begin(), command.end(), '#'), command.end());
    std::istringstream iss(command);
    std::string cmd;
    int n, X, Y, O, L;
    std::string team_name;

    std::cout << "New player: " << command << std::endl;
    if (!(iss >> cmd >> n >> X >> Y >> O >> L >> team_name)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
    {
        std::lock_guard<std::mutex> lock(_guiExecutionMutex);
        _gui.addPlayer(team_name, n, sf::Vector2f(X, _height - Y), O);
        _gui.hatchPlayer(-n);
    }
}

//ppo #n X Y O
void zappy::TCPClient::get_player_pos(std::string &command)
{
    command.erase(std::remove(command.begin(), command.end(), '#'), command.end());
    std::istringstream iss(command);
    std::string cmd;
    int n = 0, X = 0, Y = 0, O = 0;

    if (!(iss >> cmd >> n >> X >> Y >> O)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
    {
        std::lock_guard<std::mutex> lock(_guiExecutionMutex);
        _gui.updatePlayer(n, sf::Vector2f(X, _height - Y), O);
    }
}

//plv #n L
void zappy::TCPClient::get_player_level(std::string &command)
{
    command.erase(std::remove(command.begin(), command.end(), '#'), command.end());
    std::istringstream iss(command);
    std::string cmd;
    int n, L;

    if (!(iss >> cmd >> n >> L)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
    {
        std::lock_guard<std::mutex> lock(_guiExecutionMutex);
        _gui.updatePlayerLevel(n, L);
    }
}

//pin #n X Y q0 q1 q2 q3 q4 q5 q6
void zappy::TCPClient::get_player_inventory(std::string &command)
{
    command.erase(std::remove(command.begin(), command.end(), '#'), command.end());
    std::istringstream iss(command);
    std::string cmd;
    int n, X, Y, q0, q1, q2, q3, q4, q5, q6;

    if (!(iss >> cmd >> n >> X >> Y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
    {
        std::lock_guard<std::mutex> lock(_guiExecutionMutex);
        _gui.setPlayerInventory({q0, q1, q2, q3, q4, q5, q6});
    }
}

//pex #n
void zappy::TCPClient::get_player_expulsion(std::string &command)
{
    command.erase(std::remove(command.begin(), command.end(), '#'), command.end());
    std::istringstream iss(command);
    std::string cmd;
    int n;

    if (!(iss >> cmd >> n)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
}

//pbc #n message
void zappy::TCPClient::get_broadcast(std::string &command)
{
    command.erase(std::remove(command.begin(), command.end(), '#'), command.end());
    std::istringstream iss(command);
    std::string cmd;
    int n;
    std::string message;

    if (!(iss >> cmd >> n >> message)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
    //do_broadcast (not animed for now)
}

//pic X Y L #n #n ...
void zappy::TCPClient::get_incantation_start(std::string &command)
{
    command.erase(std::remove(command.begin(), command.end(), '#'), command.end());
    std::istringstream iss(command);
    std::string cmd;
    int X, Y, L, n;

    if (!(iss >> cmd >> X >> Y >> L)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
    {
        std::lock_guard<std::mutex> lock(_guiExecutionMutex);
        while (iss >> n) {
            _gui.startIncantation(n);
        }
    }
}

//pie X Y result
void zappy::TCPClient::get_incantation_end(std::string &command)
{
    std::istringstream iss(command);
    std::string cmd;
    int X, Y, result;

    if (!(iss >> cmd >> X >> Y >> result)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
    {
        std::lock_guard<std::mutex> lock(_guiExecutionMutex);
        _gui.stopIncantation(sf::Vector2i(X, _height - Y));
    }

}

//pfk #n
void zappy::TCPClient::get_egg_laid_player(std::string &command)
{
    command.erase(std::remove(command.begin(), command.end(), '#'), command.end());
    std::istringstream iss(command);
    std::string cmd;
    int n;

    if (!(iss >> cmd >> n)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
    //nothing to do, it's just a notification
}

//pdr #n i
void zappy::TCPClient::get_player_drop(std::string &command)
{
    command.erase(std::remove(command.begin(), command.end(), '#'), command.end());
    std::istringstream iss(command);
    std::string cmd;
    int n, i;

    if (!(iss >> cmd >> n >> i)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
}

//pgt #n i
void zappy::TCPClient::get_player_take(std::string &command)
{
    command.erase(std::remove(command.begin(), command.end(), '#'), command.end());
    std::istringstream iss(command);
    std::string cmd;
    int n, i;

    if (!(iss >> cmd >> n >> i)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
    //nothing to do, ressources are constantly actualized
}

//pdi #n
void zappy::TCPClient::get_player_death(std::string &command)
{
    command.erase(std::remove(command.begin(), command.end(), '#'), command.end());
    std::istringstream iss(command);
    std::string cmd;
    int n;

    if (!(iss >> cmd >> n)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
    {
        std::lock_guard<std::mutex> lock(_guiExecutionMutex);
        _gui.killPlayer(n);
    }
}

//enw #e #n X Y
void zappy::TCPClient::get_egg_laid_pos(std::string &command)
{
    command.erase(std::remove(command.begin(), command.end(), '#'), command.end());
    std::istringstream iss(command);
    std::string cmd;
    int e, n, X, Y;

    if (!(iss >> cmd >> e >> n >> X >> Y)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
    {
        std::lock_guard<std::mutex> lock(_guiExecutionMutex);
        _gui.addPlayer(_gui.getTeamByPlayerId(n), e, sf::Vector2f(X, _height - Y), 0);
    }
}

//ebo #e
void zappy::TCPClient::get_egg_hatched(std::string &command)
{
    command.erase(std::remove(command.begin(), command.end(), '#'), command.end());
    std::istringstream iss(command);
    std::string cmd;
    int e;

    if (!(iss >> cmd >> e)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
    {
        std::lock_guard<std::mutex> lock(_guiExecutionMutex);
        _gui.hatchPlayer(e);
    }
}

//edi #e
void zappy::TCPClient::get_egg_death(std::string &command)
{
    command.erase(std::remove(command.begin(), command.end(), '#'), command.end());
    std::istringstream iss(command);
    std::string cmd;
    int e;

    if (!(iss >> cmd >> e)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
    {
        std::lock_guard<std::mutex> lock(_guiExecutionMutex);
        _gui.killPlayer(e);
    }
}

//sgt T
void zappy::TCPClient::get_time_unit(std::string &command)
{
    std::istringstream iss(command);
    std::string cmd;
    int T;

    if (!(iss >> cmd >> T)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
    //nothing to do, frequency not used
}

//seg team_name
void zappy::TCPClient::get_end_game(std::string &command)
{
    std::istringstream iss(command);
    std::string cmd;
    std::string team_name;

    if (!(iss >> cmd >> team_name)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
    //the winner is defined in the smg message
}

//smg message
void zappy::TCPClient::get_server_message(std::string &command)
{
    std::istringstream iss(command);
    std::string cmd;
    std::string teamName;
    int seconds;

    if (!(iss >> cmd >> teamName >> seconds)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
    {
        std::lock_guard<std::mutex> lock(_guiExecutionMutex);
        _gui.setWinner(teamName, seconds);
    }
}

//suc
void zappy::TCPClient::get_unknown_command(std::string &command)
{
    std::istringstream iss(command);
    std::string cmd;

    if (!(iss >> cmd)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
    //nothing to do
}

//sbp
void zappy::TCPClient::get_bad_parameters(std::string &command)
{
    std::istringstream iss(command);
    std::string cmd;

    if (!(iss >> cmd)) {
        throw TcpParserException("Failed to parse command: " + command);
    }
    //nothing to do
}