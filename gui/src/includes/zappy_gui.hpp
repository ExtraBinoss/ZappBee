/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** zappy_gui
*/

#pragma once

#include <mutex>
#include <deque>
#include <chrono>
#include <thread>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "map.hpp"
#include "tcp_client.hpp"
#include "team.hpp"
#include "ressource.hpp"
#include "info.hpp"
#include "utils/macros.hpp"
#include "end.hpp"

namespace zappy {
    class TCPClient;
    class LogHistory;
    class ZappyGui {
        public:
            // Constructor / Destructor
            ZappyGui();
            ~ZappyGui();
            // Getters / Setters
            std::vector<Player> getPlayersOnTile(sf::Vector2i position);
            std::shared_ptr<Player> getPlayerById(int id);
            std::shared_ptr<Team> getTeamByName(std::string name);
            void updatePlayer(int id, sf::Vector2f position, int orientation);
            void updatePlayerLevel(int id, int level);
            void setPlayerInventory(const std::array<int, 7>& inventory);
            void setTileContentMenu(const std::array<int, 7>& inventory);
            void setTileContent(sf::Vector2i position, const std::array<int, 7>& inventory);
            void setWinner(std::string winnerTeam, int seconds);
            void drawRessource(sf::Vector2i position, int type);
            void startIncantation(int id);
            void stopIncantation(sf::Vector2i position);
            void hatchPlayer(int id);
            void killPlayer(int id);
            std::string getTeamByPlayerId(int id);
            bool isTeamsInfoOpen(void) { return _teamsInfo->isOpen(); };
            bool isPlayerMenuOpen(void) { return _teamsInfo->isPlayerOpen(); };
            bool isTileInfoOpen(void) { return _tileInfo->isOpen(); };
            // Member functions
            bool init(void);
            void initMap(int width, int height);
            void initInfos(void);
            void run(TCPClient& client);
            void handleEvents(void);
            void startReadThread(void);
            void drawLogHistory(void);
            void addPlayer(std::string team_name, int id, sf::Vector2f position, int orientation);
            void addTeam(std::string name);
            void updatePlayersTilesOrder(void);
            void updateTiles(void);
            void updateTilePtr(void);
        private:
            bool _gameOver;
            bool _teamsInfoBuilt;
            bool _tileInfoBuilt;
            bool _isometric_view;
            int _height;
            std::shared_ptr<Map> _map;
            //ARessource _ressource;
            std::shared_ptr<Tile> _selectedTile;
            sf::Vector2i _mousePos;
            std::vector<std::shared_ptr<Team>> _teams;
            std::vector<std::shared_ptr<Player>> _players;
            sf::RenderWindow _window;
            sf::Event _event;
            sf::Vector2i _lastMousePosition;
            sf::View _screenView;
            sf::Clock _clock;
            float _deltaTime;
            bool _isDragging;
            std::unique_ptr<TeamsInfo> _teamsInfo;
            std::unique_ptr<TileInfo> _tileInfo;
            End _end;
    };
}
