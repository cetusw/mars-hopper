#include "Menu.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../game/Game.h"
#include "../utils/constants.h"

extern void loadTexture(sf::Texture &texture, const std::string &filePath);
extern void loadFont(sf::Font& font, const std::string &filePath);

Menu::Menu() : selectedOption(0)
{
    initBackground("../assets/menu-background.png");
}

void Menu::init(const std::string &filePath, const std::string &titleContent, const std::vector<std::string> &menuOptions)
{
    options.clear();
    loadFont(font, filePath);

    title.setFont(font);
    title.setString(titleContent);
    title.setCharacterSize(85);
    title.setFillColor(sf::Color::White);
    title.setPosition(300, 200);

    for (int i = 0; i < menuOptions.size(); ++i)
    {
        sf::Text option;
        option.setFont(font);
        option.setString(menuOptions[i]);
        option.setCharacterSize(50);
        option.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
        option.setPosition(300, static_cast<float>(600 + i * 70));
        if (i == selectedOption)
        {
            option.setString(option.getString() + " <");
        }
        options.push_back(option);
    }
}

void Menu::initSpecificMenu(const GameState &state)
{
    switch (state)
    {
        case GameState::MainMenu:
            init("../assets/fonts/SpaceMono-Bold.ttf", "Mars Hopper", {"Start", "Settings", "Exit"});
        break;
        case GameState::Settings:
            init("../assets/fonts/SpaceMono-Bold.ttf", "Settings", {"Volume", "Back"});
        break;
        case GameState::Pause:
            init("../assets/fonts/SpaceMono-Bold.ttf", "Pause", {"Continue", "Main Menu"});
        break;
        default:;
    }
}

void Menu::initBackground(const std::string &filePath)
{
    loadTexture(backgroundTexture, filePath);
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        WINDOW_WIDTH / backgroundSprite.getLocalBounds().width,
        WINDOW_HEIGHT / backgroundSprite.getLocalBounds().height
    );
}

void Menu::draw(sf::RenderWindow &window)
{
    window.clear(sf::Color(0x00, 0x00, 0x00));
    window.draw(backgroundSprite);
    window.draw(title);
    for (const auto &option : options)
    {
        window.draw(option);
    }
    window.display();
}

void Menu::handleInput(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Up)
        {
            selectedOption = (selectedOption - 1 + options.size()) % options.size();
        }
        else if (event.key.code == sf::Keyboard::Down)
        {
            selectedOption = (selectedOption + 1) % options.size();
        }
    }
}

void Menu::handleMenu(sf::RenderWindow &window, GameState &state)
{
    initSpecificMenu(state);
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            state = GameState::Exit;
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                handleOptionList(state);
            }
            else
            {
                handleInput(event);
            }
        }
    }
    draw(window);
}

void Menu::handleOptionList(GameState &state) const
{
    switch (state)
    {
        case GameState::MainMenu:
            handleMainMenuOptionList(state);
        break;
        case GameState::Settings:
            handleSettingsOptionList(state);
        break;
        case GameState::Pause:
            handlePauseOptionList(state);
        default:;
    }
}

void Menu::handleMainMenuOptionList(GameState &state) const
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

void Menu::handleSettingsOptionList(GameState &state) const
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

void Menu::handlePauseOptionList(GameState &state) const
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

int Menu::getSelectedOption() const
{
    return selectedOption;
}
