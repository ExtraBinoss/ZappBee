/*
** EPITECH PROJECT, 2024
** gui
** File description:
** pixelCollision
*/

#pragma once

#include <SFML/Graphics.hpp>

sf::Vector2i getRelativeSpritePosition(sf::Vector2i pos, bool isometric);

bool pixelCollision(sf::Sprite sprite, sf::Vector2i pos);