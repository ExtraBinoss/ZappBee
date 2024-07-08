/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Tile
*/

#include "tile.hpp"

zappy::Tile::Tile(sf::Vector2i position)
{
    _position = position;
    _players = {};
}

zappy::Tile::~Tile()
{
    std::cout << "Tile destroyed" << std::endl;
}

int zappy::Tile::getRessource(int type)
{
    int count = 0;

    for (auto ressource : _ressources) {
        if (ressource->getType() == type)
            count++;
    }
    return count;
}

void zappy::Tile::addRessource(std::shared_ptr<ARessource> ressource)
{
    _ressources.push_back(ressource);
}

void zappy::Tile::deleteRessource(int type)
{
    for (auto it = _ressources.begin(); it != _ressources.end();) {
        if ((*it)->getType() == type) {
            it = _ressources.erase(it);
            break;
        } else {
            ++it;
        }
    }
}

void zappy::Tile::addPlayer(std::shared_ptr<Player> player)
{
    _players.push_back(player);
}

void zappy::Tile::actualizePlayers(void)
{
    for (auto it = _players.begin(); it != _players.end(); it++) {
        if ((*it)->isAlive()
        || (*it)->getPosition().x != _position.x || (*it)->getPosition().y != _position.y) {
            _players.erase(it);
            return;
        }
    }
}

void zappy::Tile::updatePlayers(sf::RenderWindow *window, bool isometric, float deltaTime)
{
    for (auto player : _players) {
        player->update(window, isometric, deltaTime);
    }
}

void zappy::Tile::updateRessources(sf::RenderWindow *window, float deltaTime)
{
    for (auto ressource : _ressources)
        ressource->update(window, false, deltaTime);
}

void zappy::Tile::update(sf::RenderWindow *window, bool isometric, float deltaTime)
{
    (void)isometric;
    updatePlayers(window, false, deltaTime);
    updateRessources(window, deltaTime);
}

void zappy::Tile::swap_view(bool isometric)
{
    for (auto ressource : _ressources)
        ressource->swap_view(isometric);
}
