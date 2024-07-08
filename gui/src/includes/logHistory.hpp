/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** logHistory.hpp
*/

#pragma once
#include <deque>
#include <string>
#include <mutex>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace zappy {
    class LogHistory {
        public:
            LogHistory() {};
            LogHistory(std::string title, sf::Vector2f pos) {
                _title.setString(title);
                _title.setCharacterSize(20);
                _title.setFillColor(sf::Color::White);
                _title.setPosition(pos);
                if (!_font.loadFromFile("gui/assets/fonts/Garet.ttf"))
                    std::cerr << "Error loading font" << std::endl;
            }

            ~LogHistory() { std::cout << "LogHistory destroyed" << std::endl; };

            void addLog(std::string log) {
                std::lock_guard<std::mutex> lock(_mutex);
                _logs.push_back(log);
                std::cout << log << std::endl;
                if (_logs.size() > 15)
                    _logs.pop_back();
            }
            void drawLogHistory(sf::RenderWindow *_window) {
                std::lock_guard<std::mutex> lock(_mutex);
                if (!_logs.empty()) {
                        float blockHeight = _logs.size() * 20 + 10;
                        sf::RectangleShape backgroundBlock(sf::Vector2f(_window->getSize().x - 20, blockHeight));
                        backgroundBlock.setPosition(10, 10);
                        backgroundBlock.setFillColor(sf::Color::Black);
                    for (size_t i = 0; i < _logs.size(); i++) {
                        sf::Text text;
                        text.setFont(_font);
                        text.setString(_logs[i]);
                        text.setCharacterSize(20);
                        text.setFillColor(sf::Color::White);
                        text.setPosition(10, 10 + i * 20);
                        _window->draw(text);
                    }
                }
            }
        protected:
        private:
            sf::Text _title;
            sf::Font _font;
            std::deque<std::string> _logs;
            std::mutex _mutex;
        };
}
