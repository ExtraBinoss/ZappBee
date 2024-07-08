/*
** EPITECH PROJECT, 2024
** gui
** File description:
** hue
*/

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <tuple>
#include <cmath>
#include "utils/colors.hpp"

std::tuple<float, float, float> rgbToHsv(sf::Color color)
{
    float r = color.r / 255.0f;
    float g = color.g / 255.0f;
    float b = color.b / 255.0f;

    float max = std::max({r, g, b});
    float min = std::min({r, g, b});
    float diff = max - min;

    float h = 0.0f;
    if (max == min) {
        h = 0.0f;
    } else if (max == r) {
        h = 60.0f * fmod(((g - b) / diff), 6.0f);
    } else if (max == g) {
        h = 60.0f * (((b - r) / diff) + 2.0f);
    } else if (max == b) {
        h = 60.0f * (((r - g) / diff) + 4.0f);
    }

    float s = (max == 0.0f) ? 0.0f : (diff / max);

    return std::make_tuple(h, s, max);
}

sf::Color hsvToRgb(float h, float s, float v)
{
    float c = v * s;
    float x = c * (1.0f - fabs(fmod(h / 60.0f, 2.0f) - 1.0f));
    float m = v - c;

    float r, g, b;
    if (h >= 0.0f && h < 60.0f) {
        r = c, g = x, b = 0.0f;
    } else if (h >= 60.0f && h < 120.0f) {
        r = x, g = c, b = 0.0f;
    } else if (h >= 120.0f && h < 180.0f) {
        r = 0.0f, g = c, b = x;
    } else if (h >= 180.0f && h < 240.0f) {
        r = 0.0f, g = x, b = c;
    } else if (h >= 240.0f && h < 300.0f) {
        r = x, g = 0.0f, b = c;
    } else {
        r = c, g = 0.0f, b = x;
    }

    return sf::Color((r + m) * 255, (g + m) * 255, (b + m) * 255);
}

sf::Color changeHue(sf::Color color, float delta)
{
    float h, s, v;
    std::tie(h, s, v) = rgbToHsv(color);

    h = fmod(h + delta, 360.0f);
    if (h < 0.0f) h += 360.0f;

    return hsvToRgb(h, s, v);
}

void changePixelColor(sf::Texture& texture, sf::Color targetColor, sf::Color newColor) {
    sf::Image image = texture.copyToImage();

    for (unsigned int x = 0; x < image.getSize().x; ++x) {
        for (unsigned int y = 0; y < image.getSize().y; ++y) {
            if (image.getPixel(x, y) == targetColor) {
                image.setPixel(x, y, newColor);
            }
        }
    }
    texture.loadFromImage(image);
}
