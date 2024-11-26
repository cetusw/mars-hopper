#include "MainMenu.h"

#include <iostream>

#include "../utils/LoadFont.h"

MainMenu::MainMenu() : selectedOption(0)
{
    init();
}

void MainMenu::init()
{
    loadFont(font, "../assets/fonts/SpaceMono-Bold.ttf");

    title.setFont(font);
    title.setString("Mars Hopper");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(300, 100);

    const std::vector<std::string> menuOptions = {"Start", "Settings", "Exit"};
    for (int i = 0; i < menuOptions.size(); ++i)
    {
        sf::Text option;
        option.setFont(font);
        option.setString(menuOptions[i]);
        option.setCharacterSize(30);
        option.setFillColor(i == selectedOption ? sf::Color::Red : sf::Color::White);
        option.setPosition(300, 200 + i * 50);
        options.push_back(option);
    }
}

void MainMenu::draw(sf::RenderWindow &window)
{
    window.draw(title);
    for (const auto &option : options)
    {
        window.draw(option);
    }
}

void MainMenu::handleInput(sf::Event event)
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
        else if (event.key.code == sf::Keyboard::Enter)
        {

        }

        for (size_t i = 0; i < options.size(); ++i)
        {
            options[i].setFillColor(i == selectedOption ? sf::Color::Red : sf::Color::White);
        }
    }
}

void MainMenu::handleMainMenu(sf::RenderWindow &window, GameState &state)
{
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
                std::cout << selectedOption;
                switch (selectedOption)
                {
                    case 0:
                        state = GameState::Playing;
                    break;
                    case 1:
                        state = GameState::Settings;
                    break;
                    case 2:
                        state = GameState::Exit;
                    break;
                    default: state = GameState::Playing;
                }
            }
            else
            {
                handleInput(event);
            }
        }
    }

    window.clear();
    draw(window);
    window.display();
}

int MainMenu::getSelectedOption() const
{
    return selectedOption;
}
