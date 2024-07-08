/*
** EPITECH PROJECT, 2024
** gui
** File description:
** info
*/

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "team.hpp"
#include "tile.hpp"

namespace zappy {
    class IInfo {
        public:
            virtual void display() = 0;
            virtual void hide() = 0;
            virtual bool isHover(sf::Vector2i cursor) = 0;
            virtual void update(sf::RenderWindow *window) = 0;
    };

    class PlayerInfo : public IInfo {
        public:
            PlayerInfo();
            ~PlayerInfo();
            void display() override { _display = true; }
            void hide() override { _display = false; }
            std::shared_ptr<Player> getFocusPlayer() { return _focusPlayer; }
            bool isHover(sf::Vector2i cursor) override;
            void setPlayer(std::shared_ptr<Player> player) { _focusPlayer = player; }
            void setPlayerInventory(const std::array<int, 7>& inventory);
            void update(sf::RenderWindow *window) override;
            bool isOpen() { return _display; };
        private:
            bool _display;
            std::array<int, 7> _inventory;
            std::shared_ptr<Player> _focusPlayer;
            std::shared_ptr<sf::Texture> _food_texture;
            std::shared_ptr<sf::Texture> _jewel_texture;
            sf::Sprite _ressource_sprite;
            sf::RectangleShape _background;
            sf::RectangleShape _teamOutline;
            sf::Font _font;
            sf::Text _text;
    };

class TeamsInfo : public IInfo {
        public:
            TeamsInfo() = default;
            TeamsInfo(std::vector<std::shared_ptr<Team>> teams);
            ~TeamsInfo();
            void display() override { _display = true; }
            void hide() override { _display = false; }
            void displayPlayerInfo() { _playerInfo.display(); }
            void hidePlayerInfo() { _playerInfo.hide(); }
            void setPlayerInventory(const std::array<int, 7>& inventory) { _playerInfo.setPlayerInventory(inventory); }
            int getCurrentTeam() { return _currentTeam; }
            int getPlayersPage() { return _playersPage; }
            int getclickedButton(sf::Vector2i cursor);
            int getPlayerClicked(sf::Vector2i cursor);
            int getFocusPlayerId() { return _playerInfo.getFocusPlayer()->getId(); }
            bool isOpen() { return _display; };
            bool isPlayerOpen() { return _playerInfo.isOpen(); };
            bool isHover(sf::Vector2i cursor) override;
            void setTeam(int teamId);
            void nextTeam() { setTeam(_currentTeam + 1); }
            void prevTeam() { setTeam(_currentTeam - 1); }
            void setPlayersPage(int page);
            void nextPlayersPage() { setPlayersPage(_playersPage + 1); }
            void prevPlayersPage() { setPlayersPage(_playersPage - 1); }
            void setPlayerInfo(int pageId);
            void updateButtons(sf::Vector2i cursor);
            void update(sf::RenderWindow *window) override;
        private:
            bool _display;
            int _currentTeam;
            int _playersPage;
            std::vector<std::shared_ptr<Team>> _teams;
            std::shared_ptr<Team> _focusTeam;
            std::vector<std::shared_ptr<Player>> _players;
            std::shared_ptr<sf::Texture> _aliveTexture;
            std::shared_ptr<sf::Texture> _deadTexture;
            std::shared_ptr<sf::Texture> _eggTexture;
            std::shared_ptr<sf::Texture> _evolvingTexture;
            std::shared_ptr<sf::Texture> _lbuttonTexture;
            std::shared_ptr<sf::Texture> _rbuttonTexture;
            sf::Sprite _playerIcon;
            sf::Sprite _buttonSprite[4];
            sf::RectangleShape _background;
            sf::Font _font;
            sf::Text _teamName;
            sf::Text _playersName;
            sf::Text _pageText;
            PlayerInfo _playerInfo;
    };

    class TileInfo : public IInfo {
        public:
            TileInfo() = default;
            TileInfo(std::shared_ptr<Tile> &tile);
            ~TileInfo();
            void display() override { _display = true; }
            void hide() override { _display = false; }
            bool isHover(sf::Vector2i cursor) override;
            void updateTile(std::shared_ptr<Tile> tile) { _focusTile = tile; }
            void setTile(std::shared_ptr<Tile> tile);
            void setTileRessources(const std::array<int, 7>& ressources);
            void setPlayersPage(int page);
            void nextPlayersPage() { setPlayersPage(_playersPage + 1); }
            void prevPlayersPage() { setPlayersPage(_playersPage - 1); }
            void swapMode();
            void updateButtons(sf::Vector2i cursor);
            int getclickedButton(sf::Vector2i cursor);
            bool isOpen() { return _display; };
            void update(sf::RenderWindow *window) override;
        private:
            bool _display;
            bool _displayMode;
            int _playersPage;
            std::array<int, 7> _ressources;
            std::shared_ptr<Tile> _focusTile;
            std::vector<std::shared_ptr<Player>> _tilePlayers;
            std::shared_ptr<sf::Texture> _foodTexture;
            std::shared_ptr<sf::Texture> _jewelTexture;
            std::shared_ptr<sf::Texture> _lbuttonTexture;
            std::shared_ptr<sf::Texture> _rbuttonTexture;
            std::shared_ptr<sf::Texture> _playerTexture;
            std::shared_ptr<sf::Texture> _evolvingTexture;
            sf::Sprite _playerIcon;
            sf::Sprite _ressource_sprite;
            sf::Sprite _buttonSprite[4];
            sf::RectangleShape _background;
            sf::Font _font;
            sf::Text _mode;
            sf::Text _tileInfo;
    };
}