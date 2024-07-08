/*
** EPITECH PROJECT, 2024
** gui
** File description:
** ressource
*/

#include "ressource.hpp"
#include <iostream>

namespace zappy {

    ARessource::ARessource(sf::Vector2f position, bool isometric)
    {

        _hasSpawned = false;
        _spawnTime = 0.0;
        _appeared = false;
        _tile_position = sf::Vector2i(position.x, position.y);
        _flat_ressource = std::make_shared<sf::Texture>();
        _isometric_ressource = std::make_shared<sf::Texture>();
        _spawn_bubble = std::make_shared<sf::Texture>();
        _spawn_bubble->loadFromFile("gui/assets/spawn_bubble.png");
        _position.x = ((position.x * TILE_SIZE - (_flat_ressource->getSize().x) / 2)) + std::rand() % TILE_SIZE;
        _position.y = ((position.y * TILE_SIZE - (_flat_ressource->getSize().y) / 2)) + std::rand() % TILE_SIZE;
        _spawn_position.x = _position.x - 5;
        _spawn_position.y = _position.y - 5;
        if (isometric) {
            simple_to_isometric(&_position.x, &_position.y);
            simple_to_isometric(&_spawn_position.x, &_spawn_position.y);
            _position.x += 45;
        }
        _bubble_sprite.setTextureRect(sf::IntRect(0, 0, 26, 26));
        _bubble_sprite.setTexture(*_spawn_bubble);
        _bubble_sprite.setPosition(_spawn_position);
    }

    ARessource::~ARessource()
    {
        std::cout << "Ressource destroyed" << std::endl;
    }

    void ARessource::update(sf::RenderWindow *window, bool isometric, float deltaTime)
    {
        (void)isometric;
        float timePerFrame = 1.0f / 26.0f;

        if (_appeared)
            window->draw(_ressource_sprite);
        if (!_hasSpawned) {
            if (_spawnTime < 1.0f) {
                _spawnTime += deltaTime;
                _appeared = _spawnTime >= 0.5f ? true : false;
                if (_spawnTime >= timePerFrame)
                    _bubble_sprite.setTextureRect(sf::IntRect(26 * (int)(_spawnTime / timePerFrame), 0, 26, 26));
                window->draw(_bubble_sprite);
            } else {
                _hasSpawned = true;
            }
        }
    }

    void ARessource::swap_view(bool isometric)
    {
        if (isometric) {
            _position.x -= 45;
            isometric_to_simple(&_position.x, &_position.y);
            _ressource_sprite.setTexture(*_flat_ressource);
            _ressource_sprite.setTextureRect(sf::IntRect(0, 0, _flat_ressource->getSize().x, _flat_ressource->getSize().y));
        } else {
            simple_to_isometric(&_position.x, &_position.y);
            _position.x += 45;
            _ressource_sprite.setTexture(*_isometric_ressource);
            _ressource_sprite.setTextureRect(sf::IntRect(0, 0, _isometric_ressource->getSize().x, _isometric_ressource->getSize().y));
        }
        _ressource_sprite.setPosition(_position);
        _bubble_sprite.setPosition(_position);
    }

    Food::Food(sf::Vector2f position, bool isometric) : ARessource(position, isometric)
    {
        _flat_ressource->loadFromFile("gui/assets/flat/food.png");
        _flat_ressource->setSmooth(true);
        _isometric_ressource->loadFromFile("gui/assets/isometric/food.png");
        _isometric_ressource->setSmooth(true);
        _ressource_sprite.setTexture(isometric ? *_isometric_ressource : *_flat_ressource);
        _ressource_sprite.setPosition(_position);
    }

    Food::~Food()
    {
        std::cout << "Food destroyed" << std::endl;
    }

    Linemate::Linemate(sf::Vector2f position, bool isometric) : ARessource(position, isometric)
    {
        _flat_ressource->loadFromFile("gui/assets/flat/jewel.png");
        _flat_ressource->setSmooth(true);
        _isometric_ressource->loadFromFile("gui/assets/isometric/jewel.png");
        _isometric_ressource->setSmooth(true);
        _ressource_sprite.setTexture(isometric ? *_isometric_ressource : *_flat_ressource);
        _ressource_sprite.setPosition(_position);
        _ressource_sprite.setColor(sf::Color(225, 75, 75));

    }

    Linemate::~Linemate()
    {
        std::cout << "Linemate destroyed" << std::endl;
    }

    Deraumere::Deraumere(sf::Vector2f position, bool isometric) : ARessource(position, isometric)
    {
        _flat_ressource->loadFromFile("gui/assets/flat/jewel.png");
        _flat_ressource->setSmooth(true);
        _isometric_ressource->loadFromFile("gui/assets/isometric/jewel.png");
        _isometric_ressource->setSmooth(true);
        _ressource_sprite.setTexture(isometric ? *_isometric_ressource : *_flat_ressource);
        _ressource_sprite.setPosition(_position);
        _ressource_sprite.setColor(sf::Color(120, 255, 50));
    }

    Deraumere::~Deraumere()
    {
        std::cout << "Deraumere destroyed" << std::endl;
    }

    Sibur::Sibur(sf::Vector2f position, bool isometric) : ARessource(position, isometric)
    {
        _flat_ressource->loadFromFile("gui/assets/flat/jewel.png");
        _flat_ressource->setSmooth(true);
        _isometric_ressource->loadFromFile("gui/assets/isometric/jewel.png");
        _isometric_ressource->setSmooth(true);
        _ressource_sprite.setTexture(isometric ? *_isometric_ressource : *_flat_ressource);
        _ressource_sprite.setPosition(_position);
        _ressource_sprite.setColor(sf::Color(210, 110, 210));
    }

    Sibur::~Sibur()
    {
        std::cout << "Sibur destroyed" << std::endl;
    }

    Mendiane::Mendiane(sf::Vector2f position, bool isometric) : ARessource(position, isometric)
    {
        _flat_ressource->loadFromFile("gui/assets/flat/jewel.png");
        _flat_ressource->setSmooth(true);
        _isometric_ressource->loadFromFile("gui/assets/isometric/jewel.png");
        _isometric_ressource->setSmooth(true);
        _ressource_sprite.setTexture(isometric ? *_isometric_ressource : *_flat_ressource);
        _ressource_sprite.setPosition(_position);
        _ressource_sprite.setColor(sf::Color(50, 160, 250));
    }

    Mendiane::~Mendiane()
    {
        std::cout << "Mendiane destroyed" << std::endl;
    }

    Phiras::Phiras(sf::Vector2f position, bool isometric) : ARessource(position, isometric)
    {
        _flat_ressource->loadFromFile("gui/assets/flat/jewel.png");
        _flat_ressource->setSmooth(true);
        _isometric_ressource->loadFromFile("gui/assets/isometric/jewel.png");
        _isometric_ressource->setSmooth(true);
        _ressource_sprite.setTexture(isometric ? *_isometric_ressource : *_flat_ressource);
        _ressource_sprite.setPosition(_position);
        _ressource_sprite.setColor(sf::Color(245, 245, 75));
    }

    Phiras::~Phiras()
    {
        std::cout << "Phiras destroyed" << std::endl;
    }

    Thystame::Thystame(sf::Vector2f position, bool isometric) : ARessource(position, isometric)
    {
        _flat_ressource->loadFromFile("gui/assets/flat/jewel.png");
        _flat_ressource->setSmooth(true);
        _isometric_ressource->loadFromFile("gui/assets/isometric/jewel.png");
        _isometric_ressource->setSmooth(true);
        _ressource_sprite.setTexture(isometric ? *_isometric_ressource : *_flat_ressource);
        _ressource_sprite.setPosition(_position);
    }

    Thystame::~Thystame()
    {
        std::cout << "Thystame destroyed" << std::endl;
    }
}

std::shared_ptr<zappy::ARessource> ressourceFactory(int type, sf::Vector2f position, bool isometric)
{
    switch (type) {
        case food:
            return std::make_shared<zappy::Food>(position, isometric);
        case linemate:
            return std::make_shared<zappy::Linemate>(position, isometric);
        case deraumere:
            return std::make_shared<zappy::Deraumere>(position, isometric);
        case sibur:
            return std::make_shared<zappy::Sibur>(position, isometric);
        case mendiane:
            return std::make_shared<zappy::Mendiane>(position, isometric);
        case phiras:
            return std::make_shared<zappy::Phiras>(position, isometric);
        case thystame:
            return std::make_shared<zappy::Thystame>(position, isometric);
        default:
            return nullptr;
    }
}
