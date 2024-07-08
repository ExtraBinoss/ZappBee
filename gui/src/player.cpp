/*
** EPITECH PROJECT, 2024
** gui
** File description:
** player
*/

#include "player.hpp"
#include "tile.hpp"

zappy::Player::Player(bool isometric, int id, sf::Vector2f position, int orientation, sf::Color color)
{
    _positionOnTile = (sf::Vector2i)position;
    _level = 0;
    _id = -id;
    _orientation = orientation;
    _alive = false;
    _evolving = false;
    _evolved = false;
    _evolvedTime = 0;
    _teamColor = color;
    _flat_player = std::make_shared<sf::Texture>();
    _isometric_player = std::make_shared<sf::Texture>();
    sf::IntRect spriteRect(isometric ? orientation * 45 : 0, 0, 32, isometric ? 90 : 32);
    setPosition(position, isometric);
    _sprite.setTextureRect(spriteRect);
    _flat_player->loadFromFile("gui/assets/flat/player.png"); 
    _flat_player->setSmooth(true);
    _isometric_player->loadFromFile("gui/assets/isometric/player.png");
    _isometric_player->setSmooth(true); 
    _sprite.setTexture(isometric ? *_isometric_player : *_flat_player);
    _sprite.setColor(_teamColor);
    _font.loadFromFile("gui/assets/fonts/viking.ttf");
    _text.setCharacterSize(12);
    _text.setFillColor(sf::Color::White);
    _text.setOutlineColor(_teamColor);
    _text.setOutlineThickness(2);
    _text.setString("Level Up !");
    setInventory({0, 0, 0, 0, 0, 0, 0});
}

zappy::Player::~Player()
{
    std::cout << "Player destroyed" << std::endl;
}

void zappy::Player::playerHatches(int id)
{
    _alive = true;
    _level = 1;
    _id = -id;
}

void zappy::Player::killPlayer()
{
    _alive = false;
}

void zappy::Player::setPosition(sf::Vector2f position, bool isometric)
{
    _positionOnTile = (sf::Vector2i)position;
    _position.x = position.x * TILE_SIZE + 16;
    _position.y = position.y * TILE_SIZE + 16;
    if (isometric) {
        simple_to_isometric(&_position.x, &_position.y);
        _position -= {-45 / 2, 74};
    }
    _sprite.setPosition(_position);
}

void zappy::Player::setInventory(const std::array<int, 7>& new_inventory) {
    for (int i = 0; i < 7; i++)
        _inventory[i] = new_inventory[i];
}

void zappy::Player::move(bool isometric)
{
    float x = 0;
    float y = 0;

    if (!_evolving) {
        switch (_orientation) {
            case North:
                y -= TILE_SIZE;
                break;
            case East:
                x += TILE_SIZE;
                break;
            case South:
                y += TILE_SIZE;
                break;
            case West:
                x -= TILE_SIZE;
                break;
        }
    }
    if (isometric) {
        simple_to_isometric(&x, &y);
        _position += {x, y};
    } else {
        _position += {x, y};
    }
    _sprite.setPosition(_position);
}

void zappy::Player::evolve()
{
    if (!_evolving) {
        _evolving = true;
    } else {
        _evolving = false;
        _sprite.setColor(_teamColor);
        _evolved = true;
        _level++;
        _text.setFont(_font);
    }
}

void zappy::Player::update(sf::RenderWindow *window, bool isometric, float deltaTime)
{
    (void)isometric;
    if (!_alive)
        return;
    if (_evolving)
        _sprite.setColor(changeHue(_sprite.getColor(), 1000.0 * deltaTime));
    if (_evolved) {
        if (_evolvedTime < 5.0f) {
            _evolvedTime += deltaTime;
            _text.setPosition(_position.x - 20, _position.y - 20);
            window->draw(_text);
        } else {
            _evolved = false;
            _evolvedTime = 0;
        }
    }
    window->draw(_sprite);
}

void zappy::Player::setOrientation(int orientation, bool isometric)
{
    if (_evolving)
        return;
    _orientation = orientation;
    if (!isometric)
        return;
    _sprite.setTextureRect(sf::IntRect(orientation * 45, 0, 45, 90));
}

void zappy::Player::swap_view(bool isometric)
{
    if (isometric) {
        _position += {-45 / 2, 74};
        isometric_to_simple(&_position.x, &_position.y);
        _sprite.setTextureRect(sf::IntRect(0, 0, _flat_player->getSize().x, _flat_player->getSize().y));
        _sprite.setTexture(*_flat_player);
    } else {
        simple_to_isometric(&_position.x, &_position.y);
        _position -= {-45 / 2, 74};
        _sprite.setTextureRect(sf::IntRect(_orientation * 45, 0, 45, _isometric_player->getSize().y));
        _sprite.setTexture(*_isometric_player);
    }
    _sprite.setPosition(_position);
}
