/*
** EPITECH PROJECT, 2024
** gui
** File description:
** tile
*/

#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "IObject.hpp"
#include "utils/macros.hpp"
#include "team.hpp"
#include "ressource.hpp"
#include "player.hpp"

namespace zappy
{
    class Player;

    class Tile : public IObject {
        public:
            Tile() = default;
            Tile(sf::Vector2i position);
            ~Tile();
            sf::Vector2i getPosition() { return _position; }
            std::vector<std::shared_ptr<ARessource>> getRessources() { return _ressources; }
            int getRessource(int type);
            std::vector<std::shared_ptr<Player>> getPlayers() { return _players; }
            void addRessource(std::shared_ptr<ARessource> ressource);
            void deleteRessource(std::shared_ptr<ARessource> ressource);
            void deleteRessource(int type);
            void addPlayer(std::shared_ptr<Player> player);
            void actualizePlayers(void);
            void updatePlayers(sf::RenderWindow *window, bool isometric, float deltaTime);
            void updateRessources(sf::RenderWindow *window, float deltaTime);
            void update(sf::RenderWindow *window, bool isometric, float deltaTime) override;
            void swap_view(bool isometric) override;
        private:
            sf::Vector2i _position;
            std::vector<std::shared_ptr<ARessource>> _ressources;
            std::vector<std::shared_ptr<Player>> _players;
    };
}