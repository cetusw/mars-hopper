#include "Screen.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "../utils/utils.cpp"
#include "../game/Game.h"
#include "../utils/constants.h"

Screen::Screen() : selectedOption(0)
{
    initBackground(MENU_BACKGROUND_IMAGE);
}

void Screen::init(const std::string &titleContent, const std::string &subtitleContent, const std::vector<std::string> &menuOptions,
                  const std::string &alignment,
                  const sf::Color titleColor, const sf::Color subtitleColor, const sf::Color contentColor)
{
    options.clear();
    loadFont(titleFont, BOLD_FONT);
    loadFont(contentFont, BOLD_FONT);

    initLine(title, titleContent, alignment, titleColor, TITLE_FONT_SIZE, TITLE_POSITION_LEFT);
    initLine(subtitle, subtitleContent, alignment, subtitleColor, SUBTITLE_FONT_SIZE, {TITLE_POSITION_LEFT.x, TITLE_POSITION_LEFT.y + 100});
    initOptionList(menuOptions, contentColor);
}

void Screen::initLine(sf::Text &text, const std::string &titleContent, const std::string &alignment, const sf::Color color, const int &characterSize,
                      const sf::Vector2f position) const
{
    text.setFont(titleFont);
    text.setString(titleContent);
    text.setCharacterSize(characterSize);
    text.setFillColor(color);
    if (alignment == "left")
    {
        text.setPosition(position);
    } else if (alignment == "center")
    {
        text.setPosition(WINDOW_WIDTH / 2 - text.getGlobalBounds().width / 2, TITLE_POSITION_LEFT.y);
    }
}

void Screen::initOptionList(const std::vector<std::string> &menuOptions, const sf::Color color)
{
    for (int i = 0; i < menuOptions.size(); ++i)
    {
        sf::Text option;
        option.setFont(contentFont);
        option.setString(menuOptions[i]);
        option.setCharacterSize(SUBTITLE_FONT_SIZE);
        option.setFillColor(color);
        option.setPosition(300, static_cast<float>(600 + i * 70));
        if (i == selectedOption)
        {
            option.setString(option.getString() + " <");
        }
        options.push_back(option);
    }
}

void Screen::initSpecificScreen(const GameState &state, const std::string &score)
{
    switch (state)
    {
        case GameState::MainMenu:
            init("Mars Hopper", "Your best score: " + std::to_string(loadProgress()), OPTIONS_MAIN_MENU, "left", sf::Color::White, sf::Color::White,
                 sf::Color::White);
            break;
        case GameState::Settings:
            init("Settings", "", OPTIONS_SETTINGS, "left", sf::Color::White, sf::Color::White, sf::Color::White);
            break;
        case GameState::GameOver:
            init(score, "", OPTIONS_GAME_OVER, "center", sf::Color::Red, sf::Color::White, sf::Color::White);
            break;
        case GameState::Pause:
            init("Pause", "", OPTIONS_PAUSE, "left", sf::Color::White, sf::Color::White, sf::Color::White);
            break;
        case GameState::Achievements:
            init("Achievements", "", getAchievementsList(), "left", sf::Color::White, sf::Color::White, sf::Color::White);
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
    window.draw(subtitle);
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

void Screen::handleScreen(sf::RenderWindow &window, GameState &state, const std::string &score)
{
    initSpecificScreen(state, score);
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

void Screen::handleOptionList(GameState &state)
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
        case GameState::Achievements:
            handleAchievementsList(state);
            break;
        case GameState::Pause:
            handlePauseOptionList(state);
        default: ;
    }
}

void Screen::handleMainMenuOptionList(GameState &state)
{
    switch (selectedOption)
    {
        case 0:
            state = GameState::Start;
            selectedOption = 0;
            break;
        case 1:
            state = GameState::Settings;
            selectedOption = 0;
            break;
        case 2:
            state = GameState::Achievements;
            selectedOption = 0;
            break;
        case 3:
            state = GameState::Exit;
            selectedOption = 0;
            break;
        default: state = GameState::MainMenu;
    }
}

void Screen::handleSettingsOptionList(GameState &state)
{
    switch (selectedOption)
    {
        case 0:
            state = GameState::Exit;
            selectedOption = 0;
            break;
        case 1:
            state = GameState::MainMenu;
            selectedOption = 0;
            break;
        default: state = GameState::Settings;
    }
}

void Screen::handlePauseOptionList(GameState &state)
{
    switch (selectedOption)
    {
        case 0:
            state = GameState::Playing;
            selectedOption = 0;
            break;
        case 1:
            state = GameState::MainMenu;
            selectedOption = 0;
            break;
        default: state = GameState::Pause;
    }
}

void Screen::handleGameOverOptionList(GameState &state)
{
    switch (selectedOption)
    {
        case 0:
            state = GameState::Start;
            selectedOption = 0;
            break;
        case 1:
            state = GameState::MainMenu;
            selectedOption = 0;
            break;
        default: state = GameState::Pause;
    }
}

void Screen::handleAchievementsList(GameState &state)
{
    if (selectedOption == options.size() - 1)
    {
        state = GameState::MainMenu;
        selectedOption = 0;
    }
}

int Screen::getSelectedOption() const
{
    return selectedOption;
}

std::vector<std::string> Screen::getAchievementsList()
{
    std::vector<std::string> achievements;
    std::ifstream inFile = loadFileForRead(ACHIEVEMENTS_FILE);

    std::string line;

    while (std::getline(inFile, line))
    {
        achievements.emplace_back(line);
    }

    if (!achievements.empty())
    {
        achievements.emplace_back("Back");
        return achievements;
    }
    achievements.emplace_back("It seems you haven't received any achievements yet");
    achievements.emplace_back("Back");
    return achievements;
}
