/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** zappy_gui
*/

#include "zappy_gui.hpp"

namespace zappy {
    ZappyGui::ZappyGui()
    {
    }

    ZappyGui::~ZappyGui()
    {
    }

    void ZappyGui::updateTiles(void)
    {
        for (auto &tile : _map->getTiles()) {
            tile->actualizePlayers();
        }
    }

    void ZappyGui::handleEvents(void)
    {
        if (_event.type == sf::Event::MouseButtonPressed) {
            if (_event.mouseButton.button == sf::Mouse::Right) {
                _isDragging = true;
                _lastMousePosition = sf::Mouse::getPosition(_window);
            }
            if (_event.mouseButton.button == sf::Mouse::Left) {
                if (!_teamsInfo->isHover(_mousePos) && !_tileInfo->isHover(_mousePos)
                &&(_map->getHoverTilePos().x != -1 && _map->getHoverTilePos().y != -1)) {
                    _selectedTile = _map->getTileOnMap(_map->getHoverTilePos());
                    _map->setSelectedTile(_selectedTile->getPosition());
                    _tileInfo->setTile(_selectedTile);
                    _tileInfo->display();
                    _teamsInfo->hide();
                }
                if (_map->getHoverTilePos().x == -1 && _map->getHoverTilePos().y == -1
                && !_teamsInfo->isHover(_mousePos) && !_tileInfo->isHover(_mousePos)) {
                    _tileInfo->hide();
                    _teamsInfo->display();
                    _map->setSelectedTile({-1, -1});
                }
                if (_teamsInfo->isHover(_mousePos)) {
                    switch (_teamsInfo->getclickedButton(_mousePos)) {
                        case 0:
                            _teamsInfo->prevTeam();
                            break;
                        case 1:
                            _teamsInfo->nextTeam();
                            break;
                        case 2:
                            _teamsInfo->prevPlayersPage();
                            break;
                        case 3:
                            _teamsInfo->nextPlayersPage();
                            break;
                        default:
                            break;
                    }
                    _teamsInfo->setPlayerInfo(_teamsInfo->getPlayerClicked(_mousePos));
                }
                if (_tileInfo->isHover(_mousePos)) {
                    switch (_tileInfo->getclickedButton(_mousePos)) {
                        case 0:
                            _tileInfo->swapMode();
                            break;
                        case 1:
                            _tileInfo->swapMode();
                            break;
                        case 2:
                            _tileInfo->nextPlayersPage();
                            break;
                        case 3:
                            _tileInfo->prevPlayersPage();
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        if (_event.type == sf::Event::MouseButtonReleased) {
            if (_event.mouseButton.button == sf::Mouse::Right) {
                _isDragging = false;
            }
        }
        if (_event.type == sf::Event::MouseMoved) {
            if (_isDragging) {
                sf::Vector2i currentMousePosition = sf::Mouse::getPosition(_window);
                sf::Vector2i delta = _lastMousePosition - currentMousePosition;
                _map->move_camera(delta.x, delta.y);
                _lastMousePosition = currentMousePosition;
            }
        }
        if (_event.type == sf::Event::Closed)
            _window.close();
        if (_event.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, _event.size.width, _event.size.height);
            _window.setView(sf::View(visibleArea));
        }
        if (_event.type == sf::Event::KeyPressed) {
            if (_event.key.code == sf::Keyboard::Escape)
                _window.close();
            if (_event.key.code == sf::Keyboard::BackSpace) {
                _tileInfo->hide();
                _teamsInfo->display();
                _teamsInfo->hidePlayerInfo();
                _map->setSelectedTile({-1, -1});
            }
            if (_event.key.code == sf::Keyboard::D)
                _map->move_camera(10, 0);
            if (_event.key.code == sf::Keyboard::Q)
                _map->move_camera(-10, 0);
            if (_event.key.code == sf::Keyboard::Z)
                _map->move_camera(0, -10);
            if (_event.key.code == sf::Keyboard::S)
                _map->move_camera(0, 10);
            if (_event.key.code == sf::Keyboard::P)
                _map->zoom_camera(0.80);
            if (_event.key.code == sf::Keyboard::M)
                _map->zoom_camera(1.20);
            if (_event.key.code == sf::Keyboard::V) {
                _map->swap_view(_isometric_view);
                for (auto &team : _teams)
                    team->swap_view(_isometric_view);
                _isometric_view = !_isometric_view;
            }
            if (_event.key.code == sf::Keyboard::W) {
                setWinner("name1", 10);
            }
            if (_event.key.code == sf::Keyboard::E) {
                initMap(10, 10);
            }
        }
    }

    std::shared_ptr<Player> ZappyGui::getPlayerById(int id)
    {
        for (auto &player : _players)
            if (player->getId() == id)
                return player;
        return nullptr;
    }

    std::shared_ptr<Team> ZappyGui::getTeamByName(std::string name)
    {
        for (auto &team : _teams)
            if (team->getName().compare(name) == 0)
                return team;
        return nullptr;
    }

    void ZappyGui::updatePlayersTilesOrder(void)
    {
        for (auto tile : _map->getTiles()) {
            if (tile->getPlayers().empty())
                continue;
            tile->updatePlayers(&_window, _isometric_view, _deltaTime);
        }
    }

    void ZappyGui::run(TCPClient &tcp)
    {
        while (_window.isOpen() && !_gameOver) {
            tcp.selectTcp();
            _deltaTime = _clock.restart().asSeconds();
            _mousePos = sf::Mouse::getPosition(_window);
            if (_teamsInfoBuilt) {
                if (isPlayerMenuOpen()) {
                    tcp.sendMessage("pin " + std::to_string(_teamsInfo->getFocusPlayerId()) + "\n");
                }
            }
            while (_window.pollEvent(_event))
                handleEvents();
            if (_tileInfoBuilt) {
                _window.setView(_map->get_camera());
            }
            _window.clear(sf::Color(61, 159, 245));
            if (_tileInfoBuilt && _teamsInfoBuilt) {
                _map->updateMap(&_window, _isometric_view, _mousePos,
                _teamsInfo->isHover(_mousePos) || _tileInfo->isHover(_mousePos));
            }
            if (_teamsInfoBuilt)
                for (auto &team : _teams)
                    team->drawSpawn(&_window);
            if (_tileInfoBuilt) {
                _map->updateRessources(&_window, _deltaTime);
                updateTiles();
                updatePlayersTilesOrder();
            }
            for (auto &player : _players)
                player->update(&_window, _isometric_view, _deltaTime);
            _window.setView(_window.getDefaultView());
            // if (_teamsInfoBuilt && _tileInfoBuilt) {
            //     _teamsInfo->updateButtons(_mousePos);
            //     _teamsInfo->update(&_window);
            //     _tileInfo->updateButtons(_mousePos);
            //     _tileInfo->update(&_window);
            // }
            if (_tileInfoBuilt)
                _map->setCamera(&_window);
            _window.display();
        }
        if (_gameOver) {
            _window.setView(_window.getDefaultView());
            _end.run(_window);
            tcp.closeConnection();
        }
    }
}
