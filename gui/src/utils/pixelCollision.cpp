/*
** EPITECH PROJECT, 2024
** gui
** File description:
** pixelCollision
*/

#include "utils/pixelCollision.hpp"

sf::Vector2i getRelativeSpritePosition(sf::Vector2i pos, bool isometric)
{
    pos.x *= pos.x < 0 ? -1 : 1;
    pos.y *= pos.y < 0 ? -1 : 1;

    return isometric ?
    (sf::Vector2i){pos.x % 90, pos.y % 45} :
    (sf::Vector2i){pos.x % 64, pos.y % 64};
}

bool pixelCollision(sf::Sprite sprite, sf::Vector2i pos)
{
    sf::Image image = sprite.getTexture()->copyToImage();
    sf::Color color = image.getPixel(pos.x, pos.y);
    return color.a != 0;
}
