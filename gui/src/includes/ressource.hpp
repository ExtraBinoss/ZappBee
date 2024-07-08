/*
** EPITECH PROJECT, 2024
** gui
** File description:
** ressource
*/

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "utils/views.hpp"
#include "utils/macros.hpp"
#include "IObject.hpp"

namespace zappy {
    class ARessource : public IObject {
        public:
            ARessource() = default;
            ARessource(sf::Vector2f position, bool isometric);
            ~ARessource();
            virtual int getType() = 0;
            sf::Vector2i getTilePosition() { return _tile_position; }
            void update(sf::RenderWindow *window, bool isometric, float deltaTime) override;
            void swap_view(bool isometric) override;
        protected:
            bool _hasSpawned;
            float _spawnTime;
            bool _appeared;
            int _type;
            sf::Vector2i _tile_position;
            sf::Vector2f _position;
            sf::Vector2f _spawn_position;
            sf::Sprite _ressource_sprite;
            sf::Sprite _bubble_sprite;
            std::shared_ptr<sf::Texture> _flat_ressource;
            std::shared_ptr<sf::Texture> _isometric_ressource;
            std::shared_ptr<sf::Texture> _spawn_bubble;
    };


    class Food : public ARessource {
        public:
            Food(sf::Vector2f position, bool isometric);
            ~Food();
            int getType() { return food; }
    };

    class Linemate : public ARessource {
        public:
            Linemate(sf::Vector2f position, bool isometric);
            ~Linemate();
            int getType() { return linemate; }

    };

    class Deraumere : public ARessource {
        public:
            Deraumere(sf::Vector2f position, bool isometric);
            ~Deraumere();
            int getType() { return deraumere; }
    };

    class Sibur : public ARessource {
        public:
            Sibur(sf::Vector2f position, bool isometric);
            ~Sibur();
            int getType() { return sibur; }
    };

    class Mendiane : public ARessource {
        public:
            Mendiane(sf::Vector2f position, bool isometric);
            ~Mendiane();
            int getType() { return mendiane; }
    };

    class Phiras : public ARessource {
        public:
            Phiras(sf::Vector2f position, bool isometric);
            ~Phiras();
            int getType() { return phiras; }
    };

    class Thystame : public ARessource {
        public:
            Thystame(sf::Vector2f position, bool isometric);
            ~Thystame();
            int getType() { return thystame; }
    };
}

std::shared_ptr<zappy::ARessource> ressourceFactory(int type, sf::Vector2f position, bool isometric);
