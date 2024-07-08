/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** end
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>


namespace zappy {

    class Confetti {
        public:
            Confetti(sf::Vector2f position, sf::Color color, float size, int rotateSpeed);
            ~Confetti();
            sf::RectangleShape getParticle() { return _particle; }
            void update(sf::RenderWindow& window, float deltaTime);
        private:
            int _rotateSpeed;
            float _size;
            sf::Vector2f _velocity;
            sf::RectangleShape _particle;
    };

    class End {
        public:
            End();
            ~End();
            void setWinner(std::string winnerTeam, sf::Color winnerColor, int seconds);
            void run(sf::RenderWindow& window);
            void addConfetti(sf::Vector2f position, sf::Color color, float size);
            void setGradient(sf::RenderWindow& window, sf::Color baseColor);
        private:
            std::vector<Confetti> _confettis;
            sf::Font _font;
            sf::Text _winnerText;
            sf::Text _timeText;
            sf::Color _winnerColor;
            std::string _winnerTeam;
    };
}