#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../utils/GameDifficulty.h"
#include "../utils/GameState.h"

class Screen
{
public:
    Screen();

    void draw(sf::RenderWindow &window);

    void handleInput(sf::Event event);

    void handleScreen(::sf::RenderWindow &window, GameState &state, GameDifficulty &difficulty, const std::string &score);

    void handleOptionList(GameState &state, GameDifficulty &difficulty);

    void handleMainMenuOptionList(GameState &state);

    void handleSettingsOptionList(GameState &state);

    void handlePauseOptionList(GameState &state);

    void handleGameOverOptionList(GameState &state);

    void handleAchievementsList(GameState &state);

    void handleDifficultyList(GameState &state, GameDifficulty &difficulty);

    int getSelectedOption() const;

    static std::vector<std::string> getAchievementsList();

private:
    void init(const std::string &titleContent, const std::string &subtitleContent, const std::vector<std::string> &menuOptions,
              const std::string &alignment,
              sf::Color titleColor, sf::Color subtitleColor, sf::Color contentColor);

    void initLine(sf::Text &text, const std::string &titleContent, const std::string &alignment, sf::Color color, const int &characterSize,
                  sf::Vector2f position) const;

    void initOptionList(const std::vector<std::string> &menuOptions, sf::Color color);

    void initSpecificScreen(const GameState &state, const std::string &score);

    void initBackground(const std::string &filePath);

    sf::Font titleFont;
    sf::Font contentFont;
    sf::Text title;
    sf::Text subtitle;
    std::vector<sf::Text> options;
    int selectedOption;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
};

#endif //MAINMENU_H
