#include "Screen.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "../utils/utils.cpp"
#include "../game/Game.h"
#include "../utils/constants.h"

Screen::Screen() : selectedOption(0)
{
    initBackground("../assets/menu-background.png");
}

void Screen::init(const std::string &titleContent, const std::vector<std::string> &menuOptions, const std::string &alignment,
                  const sf::Color titleColor, const sf::Color contentColor)
{
    options.clear();
    loadFont(titleFont, BOLD_FONT);
    loadFont(contentFont, BOLD_FONT);

    title.setFont(titleFont);
    title.setString(titleContent);
    title.setCharacterSize(85);
    title.setFillColor(titleColor);
    if (alignment == "left")
    {
        title.setPosition(TITLE_POSITION_LEFT);
    } else if (alignment == "center")
    {
        title.setPosition(WINDOW_WIDTH / 2 - title.getGlobalBounds().width / 2, TITLE_POSITION_LEFT.y);
    }

    for (int i = 0; i < menuOptions.size(); ++i)
    {
        sf::Text option;
        option.setFont(contentFont);
        option.setString(menuOptions[i]);
        option.setCharacterSize(50);
        option.setFillColor(contentColor);
        option.setPosition(300, static_cast<float>(600 + i * 70));
        if (i == selectedOption)
        {
            option.setString(option.getString() + " <");
        }
        options.push_back(option);
    }
}

void Screen::initSpecificScreen(const GameState &state)
{
    switch (state)
    {
        case GameState::MainMenu:
            init("Mars Hopper", OPTIONS_MAIN_MENU, "left", sf::Color::White, sf::Color::White);
            break;
        case GameState::Settings:
            init("Settings", OPTIONS_SETTINGS, "left", sf::Color::White, sf::Color::White);
            break;
        case GameState::GameOver:
            init("You Lose", OPTIONS_GAME_OVER, "center", sf::Color::Red, sf::Color::White);
            break;
        case GameState::Pause:
            init("Pause", OPTIONS_PAUSE, "left", sf::Color::White, sf::Color::White);
            break;
        default: ;
    }
}

void Screen::initBackground(const std::string &filePath)
{
    loadTexture(backgroundTexture, filePath);
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        WINDOW_WIDTH / backgroundSprite.getLocalBounds().width,
        WINDOW_HEIGHT / backgroundSprite.getLocalBounds().height
    );
}

void Screen::draw(sf::RenderWindow &window)
{
    window.clear(sf::Color(0x00, 0x00, 0x00));
    window.draw(backgroundSprite);
    window.draw(title);
    for (const auto &option: options)
    {
        window.draw(option);
    }
    window.display();
}

void Screen::handleInput(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Up)
        {
            selectedOption = (selectedOption - 1 + options.size()) % options.size();
        } else if (event.key.code == sf::Keyboard::Down)
        {
            selectedOption = (selectedOption + 1) % options.size();
        }
    }
}

void Screen::handleScreen(sf::RenderWindow &window, GameState &state)
{
    initSpecificScreen(state);
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            state = GameState::Exit;
        } else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                handleOptionList(state);
            } else
            {
                handleInput(event);
            }
        }
    }
    draw(window);
}

void Screen::handleOptionList(GameState &state) const
{
    switch (state)
    {
        case GameState::MainMenu:
            handleMainMenuOptionList(state);
            break;
        case GameState::Settings:
            handleSettingsOptionList(state);
            break;
        case GameState::GameOver:
            handleGameOverOptionList(state);
            break;
        case GameState::Pause:
            handlePauseOptionList(state);
        default: ;
    }
}

void Screen::handleMainMenuOptionList(GameState &state) const
{
    switch (selectedOption)
    {
        case 0:
            state = GameState::Start;
            break;
        case 1:
            state = GameState::Settings;
            break;
        case 2:
            state = GameState::Exit;
            break;
        default: state = GameState::MainMenu;
    }
}

void Screen::handleSettingsOptionList(GameState &state) const
{
    switch (selectedOption)
    {
        case 0:
            state = GameState::Exit;
            break;
        case 1:
            state = GameState::MainMenu;
            break;
        default: state = GameState::Settings;
    }
}

void Screen::handlePauseOptionList(GameState &state) const
{
    switch (selectedOption)
    {
        case 0:
            state = GameState::Playing;
            break;
        case 1:
            state = GameState::MainMenu;
            break;
        default: state = GameState::Pause;
    }
}

void Screen::handleGameOverOptionList(GameState &state) const
{
    switch (selectedOption)
    {
        case 0:
            state = GameState::Start;
            break;
        case 1:
            state = GameState::MainMenu;
            break;
        default: state = GameState::Pause;
    }
}

int Screen::getSelectedOption() const
{
    return selectedOption;
}
