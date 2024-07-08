/*
** EPITECH PROJECT, 2024
** gui
** File description:
** IObject
*/

#pragma once

#include <SFML/Graphics.hpp>

namespace zappy {
    class IObject {
    public:
        virtual ~IObject() = default;
        virtual void update(sf::RenderWindow *window, bool isometric, float deltaTime) = 0;
        virtual void swap_view(bool isometric) = 0;
    };
}
