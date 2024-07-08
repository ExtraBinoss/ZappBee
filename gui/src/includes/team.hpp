/*
** EPITECH PROJECT, 2024
** gui
** File description:
** teams
*/

#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "utils/macros.hpp"
#include "utils/views.hpp"
#include "player.hpp"

namespace zappy {
    class Player;

    class Team {
        public:
            Team() = default;
            Team(std::string name, sf::Color color);
            ~Team();
            std::vector<std::shared_ptr<Player>> getPlayers() { return _players; }
            std::string getName() { return _name; }
            sf::Color getColor() { return _color; }
            void addPlayer(std::shared_ptr<Player> player, bool isometric);
            void drawPlayers(sf::RenderWindow *window, bool isometric, float deltaTime);
            void drawSpawn(sf::RenderWindow *window);
            void swap_view(bool isometric);
        private:
            std::string _name;
            std::vector<std::shared_ptr<Player>> _players;
            sf::Vector2f _spawn;
            sf::Color _color;
            std::shared_ptr<sf::Texture> _flat_spawn_texture;
            std::shared_ptr<sf::Texture> _isometric_spawn_texture;
            sf::Sprite _spawn_sprite;
    };
}