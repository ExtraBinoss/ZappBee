/*
** EPITECH PROJECT, 2024
** gui
** File description:
** player
*/

#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <array>
#include <SFML/Graphics.hpp>
#include "IObject.hpp"
#include "utils/views.hpp"
#include "utils/colors.hpp"
#include "tile.hpp"

namespace zappy {
    class Player : public IObject {
        public:
            // Constructor / Destructor
            Player() = default;
            Player(bool isometric, int id, sf::Vector2f position, int orientation, sf::Color color);
            ~Player();
            // Member functions
            // Getters / Setters
            void setPosition(sf::Vector2f position, bool isometric);
            void setInventory(const std::array<int, 7>& new_inventory);
            void setLevel(int level) { _level = level; }
            int getId() { return _id; }
            int getLevel() { return _level; }
            int getInventory(int index) { return _inventory[index]; }
            sf::Color getColor() { return _teamColor; }
            bool isEvolving() { return _evolving; }
            bool isAlive() { return _alive; }
            bool isDead() { return !_alive && _id >= 0; }
            sf::Sprite getSprite() { return _sprite; }
            sf::Vector2f getPosition() { return _position; }
            sf::Vector2i getPositionOnTile() { return _positionOnTile; }

            void playerHatches(int id);
            void killPlayer();
            void move(bool isometric);
            void evolve();
            void update(sf::RenderWindow *window, bool isometric, float deltaTime) override;
            void drawPlayer(sf::RenderWindow *window);
            void setOrientation(int orientation, bool isometric);
            void swap_view(bool isometric) override;
        private:
            bool _alive;
            bool _evolving;
            bool _evolved;
            float _evolvedTime;
            int _id;
            int _level;
            int _inventory[7];
            sf::Vector2f _position;
            sf::Vector2i _positionOnTile;
            int _orientation;
            std::shared_ptr<sf::Texture> _flat_player;
            std::shared_ptr<sf::Texture> _isometric_player;
            sf::Sprite _sprite;
            sf::Color _teamColor;
            sf::Font _font;
            sf::Text _text;
    };
}