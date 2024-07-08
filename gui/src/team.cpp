/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Team
*/

#include "team.hpp"


zappy::Team::Team(std::string name, sf::Color color)
{
    _name = name;
    _color = color;
    _spawn = {-1, -1};
    _flat_spawn_texture = std::make_shared<sf::Texture>();
    _isometric_spawn_texture = std::make_shared<sf::Texture>();
    _flat_spawn_texture->loadFromFile("gui/assets/flat/spawn.png");
    _flat_spawn_texture->setSmooth(true);
    _isometric_spawn_texture->loadFromFile("gui/assets/isometric/spawn.png");
    _isometric_spawn_texture->setSmooth(true);
    _spawn_sprite.setTexture(*_flat_spawn_texture);
    _spawn_sprite.setColor(_color);
}

zappy::Team::~Team()
{
    std::cout << "Team destroyed" << std::endl;
}

void zappy::Team::addPlayer(std::shared_ptr<Player> player, bool isometric)
{
    float x = 16.0;
    float y = 16.0;

    if (_players.empty()) {
        _spawn = player->getPosition();
        if (isometric) {
            simple_to_isometric(&_spawn.x, &_spawn.y);
            simple_to_isometric(&x, &y);
        }
        _spawn.x -= x;
        _spawn.y -= y;
        _spawn_sprite.setPosition(_spawn);
    }
    _players.push_back(player);
}

void zappy::Team::drawPlayers(sf::RenderWindow *window, bool isometric, float deltaTime)
{
    for (auto player : _players) {
        player->update(window, isometric, deltaTime);
    }
}

void zappy::Team::drawSpawn(sf::RenderWindow *window)
{
    if (_spawn.x != -1 && _spawn.y != -1)
        window->draw(_spawn_sprite);
}

void zappy::Team::swap_view(bool isometric)
{
    for (auto player : _players)
        player->swap_view(isometric);
    if (isometric) {
        if (_spawn.x != -1 && _spawn.y != -1) {
            isometric_to_simple(&_spawn.x, &_spawn.y);
            _spawn_sprite.setPosition(_spawn);
        }
        _spawn_sprite.setTexture(*_flat_spawn_texture);
        _spawn_sprite.setTextureRect(sf::IntRect(0, 0, _flat_spawn_texture->getSize().x, _flat_spawn_texture->getSize().y));
    } else {
        if (_spawn.x != -1 && _spawn.y != -1) {
            simple_to_isometric(&_spawn.x, &_spawn.y);
            _spawn_sprite.setPosition(_spawn);
        }
        _spawn_sprite.setTexture(*_isometric_spawn_texture);
        _spawn_sprite.setTextureRect(sf::IntRect(0, 0, _isometric_spawn_texture->getSize().x, _isometric_spawn_texture->getSize().y));
    }
}