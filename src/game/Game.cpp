#include "Game.h"

#include <iostream>

#include "../utils/Constants.h"
#include "../utils/RandomGenerator.h"

Game::Game() : window(sf::VideoMode(1920, 1080), "Mars Hopper", sf::Style::Default)
{
    init();
}

void Game::init()
{
    hopper.init("../assets/crew-dragon.png");
    for (int i = 0; i < 3; i++)
    {
        platforms.emplace_back();
    }
    for (Platform &platform: platforms)
    {
        platform.init(RandomGenerator::getRandomNumber(0, WINDOW_WIDTH), RandomGenerator::getRandomNumber(0, WINDOW_HEIGHT));
    }
}

void Game::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        std::cout << hopper.getPosition().y << std::endl;
        std::cout << hopper.getAcceleration().y << std::endl;
        std::cout << hopper.getVelocity().y << std::endl;
        const float deltaTime = clock.restart().asSeconds();
        pollEvents();
        update(deltaTime);
        draw();
    }
}

void Game::pollEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        } else if (event.type == sf::Event::KeyPressed)
        {
            hopper.handleInput(event.key.code);
        }
    }
}

bool Game::collidedWithPlatform(const Hopper &hopper, const Platform &platform)
{
    return !(hopper.getPosition().y >= platform.getPosition().y + platform.getSize().height ||
             (hopper.getPosition().x + hopper.getSize().width <= platform.getPosition().x ||
              hopper.getPosition().x >= platform.getPosition().x + platform.getSize().width ||
              hopper.getPosition().y + hopper.getSize().height <= platform.getPosition().y));
}


void Game::update(const float deltaTime)
{
    hopper.updatePosition();
    bool collided = false;

    for (Platform &platform: platforms)
    {
        if (collidedWithPlatform(hopper, platform))
        {
            if (hopper.getPosition().y + hopper.getSize().height <= platform.getPosition().y + platform.getSize().height)
            {
                hopper.setVelocity({0, 0});
                hopper.setPosition({
                    hopper.getPosition().x, platform.getPosition().y - hopper.getSize().height
                });
                collided = true;
                break;
            }
        }
    }
    hopper.setPosition({hopper.getPosition().x + hopper.getVelocity().x * deltaTime, hopper.getPosition().y + hopper.getVelocity().y * deltaTime});
}

void Game::draw()
{
    window.clear(sf::Color(0x00, 0x00, 0x00));
    window.draw(hopper.getBody());
    for (Platform &currentPlatform: platforms)
    {
        window.draw(currentPlatform.getBody());
    }
    window.display();
}
