#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "../utils/GameState.h"

class Screen
{
public:
    Screen();

    void draw(sf::RenderWindow &window);

    void handleInput(sf::Event event);

    void handleScreen(sf::RenderWindow &window, GameState &state);

    void handleOptionList(GameState &state) const;

    void handleMainMenuOptionList(GameState &state) const;

    void handleSettingsOptionList(GameState &state) const;

    void handlePauseOptionList(GameState &state) const;

    void handleGameOverOptionList(GameState &state) const;

    int getSelectedOption() const;

private:
    void init(const std::string &titleContent, const std::vector<std::string> &menuOptions, const std::string &alignment, sf::Color titleColor,
              sf::Color contentColor);

    void initSpecificScreen(const GameState &state);

    void initBackground(const std::string &filePath);

    sf::Font titleFont;
    sf::Font contentFont;
    sf::Text title;
    std::vector<sf::Text> options;
    int selectedOption;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
};

#endif //MAINMENU_H
