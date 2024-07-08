/*
** EPITECH PROJECT, 2024
** gui
** File description:
** info
*/

#include "info.hpp"

namespace zappy {

    PlayerInfo::PlayerInfo()
    {
        _display = false;
        _inventory = {0, 0, 0, 0, 0, 0, 0};
        _food_texture = std::make_shared<sf::Texture>();
        _food_texture->loadFromFile("gui/assets/flat/food.png");
        _food_texture->setSmooth(true);
        _jewel_texture = std::make_shared<sf::Texture>();
        _jewel_texture->loadFromFile("gui/assets/flat/jewel.png");
        _jewel_texture->setSmooth(true);
        _background.setSize({200, 400});
        _background.setFillColor(sf::Color(0, 0, 0, 220));
        _background.setPosition(0, 0);
        _teamOutline.setSize({200, 50});
        _ressource_sprite.setTexture(*_food_texture);
        _font.loadFromFile("gui/assets/fonts/viking.ttf");
        _text.setFont(_font);
        _text.setCharacterSize(18);
        _text.setFillColor(sf::Color::White);
        _text.setOutlineColor(sf::Color::Black);
        _text.setOutlineThickness(2);
    }


    PlayerInfo::~PlayerInfo()
    {
    }

    bool PlayerInfo::isHover(sf::Vector2i cursor)
    {
        if (_display) {
            if (cursor.x >= _background.getPosition().x && cursor.x <= _background.getPosition().x + _background.getSize().x
            && cursor.y >= _background.getPosition().y && cursor.y <= _background.getPosition().y + _background.getSize().y)
                return true;
        }
        return false;
    }

    void PlayerInfo::setPlayerInventory(const std::array<int, 7>& inventory)
    {
        _inventory = inventory;
    }

    void PlayerInfo::update(sf::RenderWindow *window)
    {
        if (!_display)
            return;
        _text.setFont(_font);
        window->draw(_background);
        _teamOutline.setFillColor(_focusPlayer->isDead() ? sf::Color::White : _focusPlayer->getColor());
        window->draw(_teamOutline);
        _text.setFont(_font);
        _text.setString("PLAYER " + std::to_string(_focusPlayer->getId()));
        _text.setPosition(10, 10);
        window->draw(_text);
        _text.setFont(_font);
        _text.setString("LEVEL " + std::to_string(_focusPlayer->getLevel()));
        _text.setPosition(10, 40);
        window->draw(_text);
        _text.setFont(_font);
        if (_focusPlayer->isDead()) {
            _text.setString("DEAD");
            _text.setPosition(10, 70);
            window->draw(_text);
        } else if (!_focusPlayer->isAlive() && !_focusPlayer->isDead()) {
            _text.setString("EGG");
            _text.setPosition(10, 70);
            window->draw(_text);
        } else {
            _text.setString("INVENTORY");
            _text.setPosition(10, 70);
            window->draw(_text);
            for (int i = 0; i < 7; i++) {
                _ressource_sprite.setTexture(i == 0 ? *_food_texture : *_jewel_texture);
                _ressource_sprite.setPosition(10, 100 + i * 30);
                switch (i) {
                    case linemate:
                        _ressource_sprite.setColor(sf::Color(225, 75, 75));
                        break;
                    case deraumere:
                        _ressource_sprite.setColor(sf::Color(120, 255, 50));
                        break;
                    case sibur:
                        _ressource_sprite.setColor(sf::Color(210, 110, 210));
                        break;
                    case mendiane:
                        _ressource_sprite.setColor(sf::Color(50, 160, 250));
                        break;
                    case phiras:
                        _ressource_sprite.setColor(sf::Color(245, 245, 75));
                        break;
                    default:
                        _ressource_sprite.setColor(sf::Color::White);
                        break;
                }
                window->draw(_ressource_sprite);
                _text.setString(std::to_string(_inventory[i]));
                _text.setPosition(50, 100 + i * 30);
                window->draw(_text);
            }
        }
    }

    TeamsInfo::TeamsInfo(std::vector<std::shared_ptr<Team>> teams)
    {
        _display = true;
        _teams = teams;
        setTeam(0);
        _aliveTexture = std::make_shared<sf::Texture>();
        _aliveTexture->loadFromFile("gui/assets/flat/player.png");
        _aliveTexture->setSmooth(true);
        _deadTexture = std::make_shared<sf::Texture>();
        _deadTexture->loadFromFile("gui/assets/dead.png");
        _deadTexture->setSmooth(true);
        _eggTexture = std::make_shared<sf::Texture>();
        _eggTexture->loadFromFile("gui/assets/egg.png");
        _eggTexture->setSmooth(true);
        _evolvingTexture = std::make_shared<sf::Texture>();
        _evolvingTexture->loadFromFile("gui/assets/evolution.png");
        _evolvingTexture->setSmooth(true);
        _lbuttonTexture = std::make_shared<sf::Texture>();
        _lbuttonTexture->loadFromFile("gui/assets/button_l.png");
        _lbuttonTexture->setSmooth(true);
        _rbuttonTexture = std::make_shared<sf::Texture>();
        _rbuttonTexture->loadFromFile("gui/assets/button_r.png");
        _rbuttonTexture->setSmooth(true);
        _background.setSize({200, 500});
        _background.setFillColor(sf::Color(0, 0, 0, 220));
        _background.setOutlineColor(_focusTeam->getColor());
        _background.setOutlineThickness(5);
        _background.setPosition(960 - 200, 0);
        _font.loadFromFile("gui/assets/fonts/viking.ttf");
_font.loadFromFile("gui/assets/fonts/viking.ttf");
if (!_font.loadFromFile("gui/assets/fonts/viking.ttf")) {
    // Gérer l'échec de chargement, par exemple, en affichant un message d'erreur
    std::cerr << "Failed to load font" << std::endl;
} else {
    // Appliquer la police seulement après avoir confirmé son chargement réussi
    _teamName.setFont(_font);
    _playersName.setFont(_font);
    
    // Le reste de votre configuration de texte ici...
    _teamName.setCharacterSize(24);
    _teamName.setFillColor(sf::Color::White);
    // etc.
    
    _playersName.setCharacterSize(18);
    _playersName.setFillColor(sf::Color::White);
    // etc.
}
        // _teamName.setFont(_font);
        _teamName.setCharacterSize(24);
        _teamName.setFillColor(sf::Color::White);
        _teamName.setOutlineColor(sf::Color::Black);
        _teamName.setOutlineThickness(2);
        _teamName.setPosition(960 - 200 + 45, 15);
        // _playersName.setFont(_font);
        _playersName.setCharacterSize(18);
        _playersName.setFillColor(sf::Color::White);
        _playersName.setOutlineColor(sf::Color::Black);
        _playersName.setOutlineThickness(2);
        _playersName.setPosition(0, 0);
        _pageText.setFont(_font);
        _pageText.setCharacterSize(16);
        _pageText.setFillColor(sf::Color::White);
        _pageText.setOutlineColor(sf::Color::Black);
        _pageText.setOutlineThickness(2);
        _pageText.setPosition(960 - 200 + 50, 465);
        for (int i = 0; i < 4; i++) {
            switch (i) {
                case 0:
                    _buttonSprite[i].setPosition(960 - 200 + 10, 10);
                    break;
                case 1:
                    _buttonSprite[i].setPosition(960 - 42, 10);
                    break;
                case 2:
                    _buttonSprite[i].setPosition(960 - 200 + 10, 460);
                    break;
                case 3:
                    _buttonSprite[i].setPosition(960 - 42, 460);
                    break;
            }
            _buttonSprite[i].setTexture(i % 2 != 0 ? *_lbuttonTexture : *_rbuttonTexture);
        }
        _playerInfo = PlayerInfo();
    }

    TeamsInfo::~TeamsInfo()
    {
        std::cout << "TeamsInfo destroyed" << std::endl;
    }

    bool TeamsInfo::isHover(sf::Vector2i cursor)
    {
        if (_display) {
            if (cursor.x >= _background.getPosition().x && cursor.x <= _background.getPosition().x + _background.getSize().x
            && cursor.y >= _background.getPosition().y && cursor.y <= _background.getPosition().y + _background.getSize().y) {
                return true;
            }
        }
        return false;
    }

    void TeamsInfo::setTeam(int teamId)
    {
        _currentTeam = teamId < 0 ? (int)_teams.size() - 1 : teamId % (int)_teams.size();
        _currentTeam = _teams.size() == 1 ? 0 : _currentTeam;
        _focusTeam = _teams.at(_currentTeam);
        _players = _focusTeam->getPlayers();
        _playersPage = 0;
        _background.setOutlineColor(_focusTeam->getColor());
        _teamName.setString("_focusTeam->getName()");
    }

    void TeamsInfo::setPlayersPage(int page)
    {
        _playersPage = page < 0 ? (int)(_players.size() / PLAYERS_PER_PAGE)
        : page % (int)(_players.size() / PLAYERS_PER_PAGE + 1);
        _pageText.setString("Page " + std::to_string(page + 1) + "/"
        + std::to_string(_players.size() / PLAYERS_PER_PAGE + 1));
    }

    void TeamsInfo::updateButtons(sf::Vector2i cursor)
    {
        if (_display) {
            for (int i = 0; i < 4; i++) {
                if (cursor.x >= _buttonSprite[i].getPosition().x
                && cursor.x <= _buttonSprite[i].getPosition().x + _buttonSprite[i].getGlobalBounds().width
                && cursor.y >= _buttonSprite[i].getPosition().y
                && cursor.y <= _buttonSprite[i].getPosition().y + _buttonSprite[i].getGlobalBounds().height) {
                    _buttonSprite[i].setColor(sf::Color::Yellow);
                } else {
                    _buttonSprite[i].setColor(sf::Color::White);
                }
            }
        }
    }

    int TeamsInfo::getclickedButton(sf::Vector2i cursor)
    {
        for (int i = 0; i < 4; i++) {
            if (cursor.x >= _buttonSprite[i].getPosition().x
            && cursor.x <= _buttonSprite[i].getPosition().x + _buttonSprite[i].getGlobalBounds().width
            && cursor.y >= _buttonSprite[i].getPosition().y
            && cursor.y <= _buttonSprite[i].getPosition().y + _buttonSprite[i].getGlobalBounds().height) {
                return i;
            }
        }
        return -1;
    }

    int TeamsInfo::getPlayerClicked(sf::Vector2i cursor)
    {
        for (int i = 0; i < 5; i++) {
            if (cursor.x >= 960 - 200 + 10 && cursor.x <= 960 - 200 + 10 + 64
            && cursor.y >= 100 + i * 75 && cursor.y <= 100 + i * 75 + 64) {
                return i;
            }
        }
        return -1;
    }

    void TeamsInfo::setPlayerInfo(int pageId)
    {
        if (pageId < 0 || pageId * _playersPage >= PLAYERS_PER_PAGE
        || pageId + _playersPage * PLAYERS_PER_PAGE >= (int)_players.size())
            return;
        _playerInfo.setPlayer(_players[pageId + _playersPage * PLAYERS_PER_PAGE]);
        _playerInfo.display();
    }

    void TeamsInfo::update(sf::RenderWindow *window)
    {
        int j = _playersPage * PLAYERS_PER_PAGE;
    
        if (!_display)
            return;
        window->draw(_background);
        for (size_t i = 0; i < 5; i++, j++) {
            _playerIcon.setColor(sf::Color::White);
            if ((size_t)j >= _players.size())
                continue;
            if (_players[j]->isEvolving()) {
                _playerIcon.setTexture(*_evolvingTexture);
            } else if (_players[j]->isAlive()) {
                _playerIcon.setTexture(*_aliveTexture);
                _playerIcon.setColor(_focusTeam->getColor());
            } else if (_players[j]->isDead()) {
                _playerIcon.setTexture(*_deadTexture);
            } else {
                _playerIcon.setTexture(*_eggTexture);
            }
            _playerIcon.setPosition(960 - 200 + 10, 100 + i * 75);
            window->draw(_playerIcon);
            // _playersName.setString("PLAYER " + std::to_string(_players[j]->getId()));
            // _playersName.setPosition(960 - 200 + 45, 108 + i * 75);
            // _playersName.setFont(_font);
            // window->draw(_playersName);
        }
        for (int i = 0; i < 4; i++)
            window->draw(_buttonSprite[i]);
        _teamName.setFont(_font);
        //window->draw(_teamName);
        _pageText.setFont(_font);
        window->draw(_pageText);
        setPlayersPage(_playersPage);
        _playerInfo.update(window);
    }

    TileInfo::TileInfo(std::shared_ptr<Tile> &tile)
    {
        _display = false;
        setTile(tile);
        _ressources = {0, 2, 1, 4, 0, 0, 0};
        _mode.setString("RESSOURCES");
        _mode.setPosition(960 - 200 + 10, 70);
        _mode.setFont(_font);
        _mode.setCharacterSize(24);
        _mode.setFillColor(sf::Color::White);
        _mode.setOutlineColor(sf::Color::Black);
        _mode.setOutlineThickness(2);
        _playerTexture = std::make_shared<sf::Texture>();
        _playerTexture->loadFromFile("gui/assets/flat/player.png");
        _playerTexture->setSmooth(true);
        _evolvingTexture = std::make_shared<sf::Texture>();
        _evolvingTexture->loadFromFile("gui/assets/evolution.png");
        _evolvingTexture->setSmooth(true);
        _lbuttonTexture = std::make_shared<sf::Texture>();
        _lbuttonTexture->loadFromFile("gui/assets/button_l.png");
        _lbuttonTexture->setSmooth(true);
        _rbuttonTexture = std::make_shared<sf::Texture>();
        _rbuttonTexture->loadFromFile("gui/assets/button_r.png");
        _rbuttonTexture->setSmooth(true);
        _foodTexture = std::make_shared<sf::Texture>();
        _foodTexture->loadFromFile("gui/assets/flat/food.png");
        _foodTexture->setSmooth(true);
        _jewelTexture = std::make_shared<sf::Texture>();
        _jewelTexture->loadFromFile("gui/assets/flat/jewel.png");
        _jewelTexture->setSmooth(true);
        _background.setSize({200, 500});
        _background.setFillColor(sf::Color(0, 0, 0, 220));
        _background.setPosition(960 - 200, 0);
        _font.loadFromFile("gui/assets/fonts/viking.ttf");
        _tileInfo.setFont(_font);
        _tileInfo.setCharacterSize(18);
        _tileInfo.setFillColor(sf::Color::White);
        _tileInfo.setOutlineColor(sf::Color::Black);
        _tileInfo.setOutlineThickness(2);
        _playerIcon.setTexture(*_playerTexture);
        for (int i = 0; i < 4; i++) {
            _buttonSprite[i].setTexture(i % 2 != 0 ? *_lbuttonTexture : *_rbuttonTexture);
            switch (i) {
                case 0:
                    _buttonSprite[i].setPosition(960 - 200 + 10, 10);
                    break;
                case 1:
                    _buttonSprite[i].setPosition(960 - 42, 10);
                    break;
                case 2:
                    _buttonSprite[i].setPosition(960 - 200 + 10, 460);
                    break;
                case 3:
                    _buttonSprite[i].setPosition(960 - 42, 460);
                    break;
            }
        }
    }

    TileInfo::~TileInfo()
    {
    }

    void TileInfo::setTile(std::shared_ptr<Tile> tile)
    {
        _focusTile = tile;
        _displayMode = true;
        _playersPage = 0;
    }

    void TileInfo::swapMode()
    {
        _displayMode = !_displayMode;
        _mode.setString(_displayMode ? "RESSOURCES" : "PLAYERS");
        _playersPage = 0;
    }

    bool TileInfo::isHover(sf::Vector2i cursor)
    {
        if (_display) {
            if (cursor.x >= _background.getPosition().x && cursor.x <= _background.getPosition().x + _background.getSize().x
            && cursor.y >= _background.getPosition().y && cursor.y <= _background.getPosition().y + _background.getSize().y)
                return true;
        }
        return false;
    }

    void TileInfo::setTileRessources(const std::array<int, 7>& ressources)
    {
        _ressources = ressources;
    }

    void TileInfo::updateButtons(sf::Vector2i cursor)
    {
        if (_display) {
            for (int i = 0; i < 4; i++) {
                if (cursor.x >= _buttonSprite[i].getPosition().x
                && cursor.x <= _buttonSprite[i].getPosition().x + _buttonSprite[i].getGlobalBounds().width
                && cursor.y >= _buttonSprite[i].getPosition().y
                && cursor.y <= _buttonSprite[i].getPosition().y + _buttonSprite[i].getGlobalBounds().height) {
                    _buttonSprite[i].setColor(sf::Color::Yellow);
                } else {
                    _buttonSprite[i].setColor(sf::Color::White);
                }
            }
        }
    }

    int TileInfo::getclickedButton(sf::Vector2i cursor)
    {
        for (int i = 0; i < 4; i++) {
            if (cursor.x >= _buttonSprite[i].getPosition().x
            && cursor.x <= _buttonSprite[i].getPosition().x + _buttonSprite[i].getGlobalBounds().width
            && cursor.y >= _buttonSprite[i].getPosition().y
            && cursor.y <= _buttonSprite[i].getPosition().y + _buttonSprite[i].getGlobalBounds().height) {
                return i;
            }
        }
        return -1;
    }

    void TileInfo::setPlayersPage(int page)
    {
        _playersPage = page < 0 ? (int)(_tilePlayers.size() / PLAYERS_PER_PAGE)
        : page % (int)(_tilePlayers.size() / PLAYERS_PER_PAGE + 1);
    }

    void TileInfo::update(sf::RenderWindow *window)
    {
        if (!_display)
            return;
        _tilePlayers = _focusTile->getPlayers();
        int j = _playersPage * PLAYERS_PER_PAGE > (int)_tilePlayers.size() ?
        (int)(_tilePlayers.size() / PLAYERS_PER_PAGE) : _playersPage * PLAYERS_PER_PAGE;
        window->draw(_background);
        for (int i = 0; i < 2; i++)
            window->draw(_buttonSprite[i]);
        _mode.setFont(_font);
        window->draw(_mode);
        if (_displayMode) {
            for (int i = 0; i < 7; i++) {
                _ressource_sprite.setTexture(i == 0 ? *_foodTexture : *_jewelTexture);
                _ressource_sprite.setPosition(960 - 200 + 20, 100 + i * 30);
                switch (i) {
                    case linemate:
                        _ressource_sprite.setColor(sf::Color(225, 75, 75));
                        break;
                    case deraumere:
                        _ressource_sprite.setColor(sf::Color(120, 255, 50));
                        break;
                    case sibur:
                        _ressource_sprite.setColor(sf::Color(210, 110, 210));
                        break;
                    case mendiane:
                        _ressource_sprite.setColor(sf::Color(50, 160, 250));
                        break;
                    case phiras:
                        _ressource_sprite.setColor(sf::Color(245, 245, 75));
                        break;
                    default:
                        _ressource_sprite.setColor(sf::Color::White);
                        break;
                }
                window->draw(_ressource_sprite);
                _tileInfo.setString(std::to_string(_focusTile->getRessource(i)));
                _tileInfo.setPosition(960 - 200 + 50, 100 + i * 30);
                _tileInfo.setFont(_font);
                window->draw(_tileInfo);
            }
        } else {
            for (size_t i = 0; i < 5; i++, j++) {
                _playerIcon.setColor(sf::Color::White);
                if ((size_t)j >= _tilePlayers.size())
                    continue;
                _playerIcon.setTexture(_tilePlayers[j]->isEvolving() ? *_evolvingTexture : *_playerTexture);
                _playerIcon.setColor(_tilePlayers[j]->isEvolving() ? sf::Color::White : _tilePlayers[j]->getColor());
                _playerIcon.setPosition(960 - 200 + 10, 100 + i * 75);
                window->draw(_playerIcon);
                _tileInfo.setString("PLAYER " + std::to_string(_tilePlayers[j]->getId()));
                _tileInfo.setPosition(960 - 200 + 45, 108 + i * 75);
                _tileInfo.setFont(_font);
                window->draw(_tileInfo);
                for (int i = 2; i < 4; i++)
                    window->draw(_buttonSprite[i]);
            }
        }
    }

}