/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** end
*/

#include "end.hpp"
#include <iostream>

zappy::End::End()
{
    _winnerTeam = "";
}

zappy::End::~End()
{
    std::cout << "End of the game" << std::endl;
}

void zappy::End::setWinner(std::string winnerTeam, sf::Color winnerColor, int seconds)
{
    sf::Color color;

    _winnerTeam = winnerTeam;
    _winnerColor = winnerColor;
    _font.loadFromFile("gui/assets/fonts/viking.ttf");
    _winnerText.setFont(_font);
    _winnerText.setCharacterSize(24);
    _winnerText.setFillColor(sf::Color::White);
    _winnerText.setString("TEAM : " + _winnerTeam + " WINS");
    _winnerText.setPosition(960 / 2 - _winnerText.getGlobalBounds().width / 2, 540 / 2 - _winnerText.getGlobalBounds().height / 2);
    _timeText.setFont(_font);
    _timeText.setCharacterSize(24);
    _timeText.setFillColor(sf::Color::White);
    _timeText.setString("in " + std::to_string(seconds) + " seconds");
    _timeText.setPosition(960 / 2 - _timeText.getGlobalBounds().width / 2, 540 / 2 - _timeText.getGlobalBounds().height / 2 + 30);
    for (int i = 0; i < 100; ++i) {
        float size = static_cast<float>(std::rand() % 10 + 5) / 5.0;
        color = sf::Color(winnerColor.r, winnerColor.g, winnerColor.b, std::rand() % 155 + 100);
        _confettis.emplace_back(sf::Vector2f(std::rand() % 960, std::rand() % 540), color, size, (std::rand() % 9 + 1) * 10);
    }
}

void zappy::End::run(sf::RenderWindow& window)
{
    float deltaTime = 0.0f;
    sf::Clock clock;
    sf::Event event;

    while (_winnerTeam.empty())
        continue;
    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
            event.type == sf::Event::KeyPressed)
                window.close();
        }
        window.clear();
        setGradient(window, _winnerColor);
        for (auto& confetti : _confettis) {
            confetti.update(window, deltaTime * 100);
            window.draw(confetti.getParticle());
        }
        window.draw(_winnerText);
        window.draw(_timeText);
        window.display();
    }
}

void zappy::End::setGradient(sf::RenderWindow& window, sf::Color baseColor)
{
    float height = static_cast<float>(window.getSize().y);
    float numBands = 100.0f;

    for (int i = 0; i < numBands; ++i) {
        sf::RectangleShape band(sf::Vector2f(window.getSize().x, height / numBands));
        band.setPosition(0, i * (height / numBands));
        float alpha = static_cast<float>(i) / numBands;
        sf::Color bandColor = sf::Color(
            static_cast<sf::Uint8>(baseColor.r * alpha * 0.4),
            static_cast<sf::Uint8>(baseColor.g * alpha * 0.4),
            static_cast<sf::Uint8>(baseColor.b * alpha * 0.4)
        );
        band.setFillColor(bandColor);
        window.draw(band);
    }
}

zappy::Confetti::Confetti(sf::Vector2f position, sf::Color color, float size, int rotateSpeed)
{
    _size = size;
    _rotateSpeed = rotateSpeed;
    _particle.setSize(sf::Vector2f(size, size));
    _particle.setPosition({position.x + size / 2, position.y + size / 2});
    _particle.setFillColor(color);
    _velocity = sf::Vector2f(0, (std::rand() % 50 + 10) / 10.0);
}

zappy::Confetti::~Confetti()
{
}

void zappy::Confetti::update(sf::RenderWindow& window, float deltaTime)
{
    _particle.move(_velocity * deltaTime);
    _particle.rotate(_rotateSpeed * deltaTime);
    if (_particle.getPosition().y > window.getSize().y)
        _particle.setPosition(_particle.getPosition().x, 0);
}
