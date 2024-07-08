/*
** EPITECH PROJECT, 2024
** gui
** File description:
** hue
*/

#pragma once

#include <SFML/Graphics.hpp>

sf::Color changeHue(sf::Color color, float delta);
void changePixelColor(sf::Texture& texture, sf::Color targetColor, sf::Color newColor);