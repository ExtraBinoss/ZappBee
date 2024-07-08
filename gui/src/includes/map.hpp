/*
** EPITECH PROJECT, 2024
** gui
** File description:
** map
*/

#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "utils/views.hpp"
#include "utils/pixelCollision.hpp"
#include "tile.hpp"
#include "player.hpp"
#include "ressource.hpp"

namespace zappy {
    class Map {
        public:
            // Constructor / Destructor
            Map() = default;
            Map(int width, int height);
            ~Map();
            // Getters / Setters
            sf::View get_camera(void) const { return _camera; }
            sf::Vector2i getHoverTilePos() { return static_cast<sf::Vector2i>(_hoverTile); }
            sf::Vector2i getSelectedTilePos() { return _selectedTile; }
            std::vector<std::shared_ptr<Tile>> getTiles() { return _tiles; }
            std::shared_ptr<Tile> getTileOnMap(sf::Vector2i position);
            int getTileRessourceCount(sf::Vector2i position, int type);
            void setSelectedTile(sf::Vector2i tile) { _selectedTile = tile;}
            void setCamera(sf::RenderWindow *window);
            bool isInMap(sf::Vector2i cursor);
            // Member functions
            void move_camera(int x, int y);
            void zoom_camera(float zoom);
            bool tileCollision(sf::Vector2f cursor_pos);
            void swap_view(bool isometric);
            void addPlayerInTile(sf::Vector2i position, std::shared_ptr<Player> player);
            bool tileCollision(sf::Vector2f cursor_pos, bool isometric);
            void updateMap(sf::RenderWindow *window, bool isometric, sf::Vector2i cursos_pos, bool hover);
            void updateRessources(sf::RenderWindow *window, float deltaTime);
            void addRessource(sf::Vector2i position, int type, bool isometric);
            void deleteRessource(sf::Vector2i position, int type);
            void evolvePlayersOnTile(sf::Vector2i position);
        private:
            int _width;
            int _height;
            sf::Vector2i _hoverTile;
            sf::Vector2i _selectedTile;
            std::vector<std::shared_ptr<Tile>> _tiles;
            std::vector<std::shared_ptr<ARessource>> _ressources;
            std::shared_ptr<sf::Texture> _flat_tile;
            std::shared_ptr<sf::Texture> _isometric_tile;
            std::shared_ptr<sf::Texture> _flat_background;
            std::shared_ptr<sf::Texture> _isometric_background;
            sf::Sprite _sprite;
            sf::View _camera;
    };
}