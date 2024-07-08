/*
** EPITECH PROJECT, 2024
** gui
** File description:
** map
*/

#include "map.hpp"

zappy::Map::Map(int width, int height)
{
    _hoverTile = {-1, -1};
    _selectedTile = {-1, -1};
    _width = width;
    _height = height;
    for (int i = 0; i < std::min(width, height); i++) {
        _tiles.push_back(std::make_shared<Tile>(sf::Vector2i(i, i)));
        for (int j = i + 1; j < height; j++) {
            _tiles.push_back(std::make_shared<Tile>(sf::Vector2i(i, j)));
        }
        for (int j = i + 1; j < width; j++) {
            _tiles.push_back(std::make_shared<Tile>(sf::Vector2i(j, i)));
        }
    }
    if (width > height) {
        for (int i = height; i < width; i++) {
            for (int j = 0; j < height; j++) {
                _tiles.push_back(std::make_shared<Tile>(sf::Vector2i(i, j)));
            }
        }
    } else {
        for (int i = width; i < height; i++) {
            for (int j = 0; j < width; j++) {
                _tiles.push_back(std::make_shared<Tile>(sf::Vector2i(j, i)));
            }
        }
    }
    _flat_tile = std::make_shared<sf::Texture>();
    _isometric_tile = std::make_shared<sf::Texture>();
    _flat_tile->loadFromFile("gui/assets/flat/tile.png");
    _flat_tile->setSmooth(true);
    _isometric_tile->loadFromFile("gui/assets/isometric/tile.png");
    _isometric_tile->setSmooth(true);
    _sprite.setTexture(*_flat_tile);
    _camera.setSize(960, 540);
    _camera.setCenter((width * TILE_SIZE) / 2, (height * TILE_SIZE) / 2);
    // _camera.setViewport(sf::FloatRect(0, 0, 1, 1));
}

zappy::Map::~Map()
{
    std::cout << "Map destroyed" << std::endl;
}

bool zappy::Map::tileCollision(sf::Vector2f cursor_pos, bool isometric)
{
    if (isometric)
        return cursor_pos.x >= _sprite.getPosition().x && cursor_pos.x <= _sprite.getPosition().x + 90.0
        && cursor_pos.y >= _sprite.getPosition().y && cursor_pos.y <= _sprite.getPosition().y + 45.0;
    else
        return cursor_pos.x >= _sprite.getPosition().x && cursor_pos.x <= _sprite.getPosition().x + 64.0
        && cursor_pos.y >= _sprite.getPosition().y && cursor_pos.y <= _sprite.getPosition().y + 64.0;
}

void zappy::Map::updateMap(sf::RenderWindow *window, bool isometric, sf::Vector2i cursor_pos, bool hover)
{
    sf::Vector2i CursorOnSprite = {0, 0};
    sf::Vector2f tilePos = {0, 0};

    _hoverTile = {-1, -1};
    for (auto tile : _tiles) {
        tilePos = static_cast<sf::Vector2f>(tile->getPosition() * TILE_SIZE);
        if (isometric)
            simple_to_isometric(&tilePos.x, &tilePos.y);
        _sprite.setPosition(tilePos.x, tilePos.y);
        if (tileCollision(window->mapPixelToCoords(cursor_pos, _camera), isometric)  && isInMap((sf::Vector2i)tilePos) && !hover) {
            CursorOnSprite = getRelativeSpritePosition((sf::Vector2i)window->mapPixelToCoords(cursor_pos, _camera), isometric);
            if (pixelCollision(_sprite, CursorOnSprite)) {
                _sprite.setColor(sf::Color(175, 175, 255, 180));
                _hoverTile = {(int)tilePos.x, (int)tilePos.y};
            } else {
                _sprite.setColor(sf::Color::White);
            }
        } else if (tilePos.x == _selectedTile.x && tilePos.y == _selectedTile.y) {
            _sprite.setColor(sf::Color::Cyan);
        } else {
            _sprite.setColor(sf::Color::White);
        }
        window->draw(_sprite);
    }
}

bool zappy::Map::isInMap(sf::Vector2i cursor)
{
    return cursor.x >= 0 && cursor.x <= _width * TILE_SIZE
    && cursor.y >= 0 && cursor.y <= _height * TILE_SIZE;
}

void zappy::Map::move_camera(int x, int y)
{
    _camera.move(x, y);
}

void zappy::Map::zoom_camera(float zoom)
{
    _camera.zoom(zoom);
}

void zappy::Map::swap_view(bool isometric)
{
    float camera_x = _camera.getCenter().x;
    float camera_y = _camera.getCenter().y;

    for (auto &tile : _tiles)
        tile->swap_view(isometric);
    if (isometric) {
        _sprite.setTexture(*_flat_tile);
        _sprite.setTextureRect(sf::IntRect(0, 0, _flat_tile->getSize().x, _flat_tile->getSize().y));
        isometric_to_simple(&camera_x, &camera_y);
        _camera.setCenter({camera_x, camera_y});
    } else {
        _sprite.setTexture(*_isometric_tile);
        _sprite.setTextureRect(sf::IntRect(0, 0, _isometric_tile->getSize().x, _isometric_tile->getSize().y));
        simple_to_isometric(&camera_x, &camera_y);
        _camera.setCenter({camera_x, camera_y});
    }
}

void zappy::Map::updateRessources(sf::RenderWindow *window, float deltaTime)
{
    for (auto tile : _tiles)
        tile->updateRessources(window, deltaTime);
}

void zappy::Map::addRessource(sf::Vector2i tile_position, int type, bool isometric)
{
    auto new_ressource = ressourceFactory(type, (sf::Vector2f)tile_position, isometric);
    _ressources.push_back(new_ressource);
    for (auto &tile : _tiles)
        if (tile->getPosition().x == tile_position.x && tile->getPosition().y == tile_position.y) {
            tile->addRessource(_ressources.back());
            break;
        }
}

void zappy::Map::deleteRessource(sf::Vector2i tile_position, int type)
{
    for (auto it = _ressources.begin(); it != _ressources.end();) {
        if ((*it)->getType() == type && (*it)->getTilePosition().x == tile_position.x && (*it)->getTilePosition().y == tile_position.y) {
            for (auto &tile : _tiles)
                if (tile->getPosition().x == tile_position.x && tile->getPosition().y == tile_position.y) {
                    tile->deleteRessource(type);
                    break;
                }
            it = _ressources.erase(it);
            break;
        } else {
            ++it;
        }
    }
}

int zappy::Map::getTileRessourceCount(sf::Vector2i position, int type)
{
    int count = 0;

    for (auto &tile : _tiles) {
        if (tile->getPosition().x == position.x && tile->getPosition().y == position.y) {
            count = tile->getRessource(type);
            break;
        }
    }
    return count;
}

void zappy::Map::addPlayerInTile(sf::Vector2i tile_position, std::shared_ptr<Player> player)
{
    for (auto &tile : _tiles)
        if (tile->getPosition().x == tile_position.x && tile->getPosition().y == tile_position.y) {
            tile->addPlayer(player);
            break;
        }
}

std::shared_ptr<zappy::Tile> zappy::Map::getTileOnMap(sf::Vector2i position)
{
    position = {position.x / TILE_SIZE, position.y / TILE_SIZE};
    for (auto &tile : _tiles) {
        if (tile->getPosition().x == position.x && tile->getPosition().y == position.y) {
            return tile;
        }
    }
    return nullptr;
}

void zappy::Map::setCamera(sf::RenderWindow *window)
{
    window->setView(_camera);
}

void zappy::Map::evolvePlayersOnTile(sf::Vector2i position)
{
    for (auto &tile : _tiles)
        if (tile->getPosition().x == position.x && tile->getPosition().y == position.y) {
            for (auto &player : tile->getPlayers()) {
                player->evolve();
            }
            return;
        }
}
