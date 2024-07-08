/*
** EPITECH PROJECT, 2024
** gui
** File description:
** gui_serv_commands
*/

#include "zappy_gui.hpp"
#include "Exceptions.hpp"

namespace zappy {
    bool ZappyGui::init(void)
    {
        _window.create(sf::VideoMode(960, 540), "Zappy");
        if (!_window.isOpen())
            return false;
        _window.setFramerateLimit(60);
        std::srand(std::time(nullptr));
        _gameOver = false;
        _isDragging = false;
        _isometric_view = false;
        _mousePos = {0, 0};
        _teams = std::vector<std::shared_ptr<Team>>();
        _end = End();
        _teamsInfoBuilt = false;
        _tileInfoBuilt = false;
        return true;
    }

    void ZappyGui::initMap(int width, int height)
    {
        if (width < 1 || height < 1) {
            throw GUIException("Invalid map size");
        }
        _map = std::make_shared<Map>(width, height);
        _height = height - 1;
        _selectedTile = _map->getTileOnMap({0, 0});
        _tileInfo = std::make_unique<TileInfo>(_selectedTile);
        _tileInfoBuilt = true;
    }

    void ZappyGui::initInfos(void)
    {
        _teamsInfo = std::make_unique<TeamsInfo>(_teams);
        _teamsInfoBuilt = true;
    }

    void ZappyGui::addTeam(std::string name)
    {
        sf::Color color;

        switch (_teams.size() % 10) {
            case 0:
                color = sf::Color(180, 75, 255);
                break;
            case 1:
                color = sf::Color(220, 20, 60);
                break;
            case 2:
                color = sf::Color(10, 215, 185);
                break;
            case 3:
                color = sf::Color(75, 255, 90);
                break;
            case 4:
                color = sf::Color(30, 135, 210);
                break;
            case 5:
                color = sf::Color(250, 250, 10);
                break;
            case 6:
                color = sf::Color(180, 180, 255);
                break;
            case 7:
                color = sf::Color(255, 120, 145);
                break;
            case 8:
                color = sf::Color(255, 120, 40);
                break;
            case 9:
                color = sf::Color(150, 150, 20);
                break;
        }
        _teams.push_back(std::make_shared<Team>(name, color));
    }


    void ZappyGui::updatePlayer(int id, sf::Vector2f position, int orientation)
    {
        for (auto &player : _players) {
            if (player->getId() == id) {
                player->setPosition(position, _isometric_view);
                player->setOrientation(orientation, _isometric_view);
                return;
            }
        }
    }

    void ZappyGui::addPlayer(std::string team_name, int id, sf::Vector2f position, int orientation)
    {
        std::shared_ptr<Player> player = nullptr;
    
        for (auto &team : _teams)
            if (team->getName().compare(team_name) == 0) {
                player = std::make_shared<Player>(_isometric_view, id, position, orientation, team->getColor());
                _players.push_back(player);
                team->addPlayer(player, _isometric_view);
                _map->addPlayerInTile(static_cast<sf::Vector2i>(position), player);
                return;
            }
    }

    void ZappyGui::updatePlayerLevel(int id, int level)
    {
        for (auto &player : _players)
            if (player->getId() == id) {
                player->setLevel(level);
                return;
            }
    }

    void ZappyGui::setPlayerInventory(const std::array<int, 7>& inventory)
    {
        _teamsInfo->setPlayerInventory(inventory);
    }

    void ZappyGui::startIncantation(int id)
    {
        for (auto player : _players) {
            if (player->getId() == id) {
                player->evolve();
                return;
            }
        }
    }

    void ZappyGui::stopIncantation(sf::Vector2i position)
    {
        for (auto player : _players) {
            if (player->getPositionOnTile().x == position.x && player->getPositionOnTile().y == position.y) {
                player->evolve();
                return;
            }
        }
    }

    void ZappyGui::hatchPlayer(int id)
    {
        for (auto &player : _players) {
            if (player->getId() == id) {
                player->playerHatches(id);
                return;
            }
        }
    }

    void ZappyGui::killPlayer(int id)
    {
        for (auto &player : _players)
            if (player->getId() == id) {
                player->killPlayer();
                return;
            }
    }

    std::string ZappyGui::getTeamByPlayerId(int id)
    {
        for (auto &team : _teams)
            for (auto &player : team->getPlayers())
                if (player->getId() == id)
                    return team->getName();
        return "";
    }

    void ZappyGui::setTileContentMenu(const std::array<int, 7>& inventory)
    {
        _tileInfo->setTileRessources(inventory);
    }

    void ZappyGui::setTileContent(sf::Vector2i position, const std::array<int, 7>& inventory)
    {
        int count = 0;

        for (int i = 0; i < 7; i++) {
            count = _map->getTileRessourceCount(position, i);
            while (count != inventory[i]) {
                if (count < inventory[i]) {
                    _map->addRessource(position, i, _isometric_view);
                    count++;
                }
                if (count > inventory[i]) {
                    _map->deleteRessource(position, i);
                    count--;
                }
            }
        }
    }

    void ZappyGui::setWinner(std::string winnerTeam, int seconds)
    {
        bool found = false;

        _window.setView(_window.getDefaultView());
        for (auto &team : _teams) {
            if (team->getName() == winnerTeam) {
                _end.setWinner(winnerTeam, team->getColor(), seconds);
                found = true;
            }
        }
        if (!found)
            _end.setWinner(winnerTeam, sf::Color::Cyan, seconds);
        _gameOver = true;
    }
}
