#include "Game.h"

#include <iostream>

#include "../utils/Constants.h"
#include "../utils/RandomGenerator.h"
#include "../utils/TextureLoader.h"

Game::Game() : window(sf::VideoMode(1920, 1080), "Mars Hopper", sf::Style::Default)
{
    init();
}

void Game::init()
{
    vehicle.init("../assets/crew-dragon.png");
    background.init("../assets/game-background.png");
    for (int i = 0; i < 3; i++)
    {
        platforms.emplace_back();
    }
    for (Platform &platform: platforms)
    {
        platform.init(RandomGenerator::getRandomNumber(0, WINDOW_WIDTH), RandomGenerator::getRandomNumber(0, GROUND_LEVEL));
    }
}

void Game::run()
{
    float timeSinceLastUpdate = 0.0f;
    sf::Clock clock;
    while (window.isOpen())
    {
        const float deltaTime = clock.restart().asSeconds();
        timeSinceLastUpdate += deltaTime;

        pollEvents();

        while (timeSinceLastUpdate >= TIME_STEP)
        {
            update(TIME_STEP);
            timeSinceLastUpdate -= TIME_STEP;
        }

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
            vehicle.handleInput(event.key.code);
        }
    }
}

bool Game::collidedWithPlatform(const Vehicle &vehicle, const Platform &platform)
{
    return !(vehicle.getPosition().y >= platform.getPosition().y + platform.getSize().height ||
             (vehicle.getPosition().x + vehicle.getSize().width <= platform.getPosition().x ||
              vehicle.getPosition().x >= platform.getPosition().x + platform.getSize().width ||
              vehicle.getPosition().y + vehicle.getSize().height <= platform.getPosition().y));
}


void Game::update(const float deltaTime)
{
    vehicle.updatePosition();

    for (Platform &platform: platforms)
    {
        if (collidedWithPlatform(vehicle, platform))
        {
            if (vehicle.getPosition().y + vehicle.getSize().height <= platform.getPosition().y + platform.getSize().height)
            {
                vehicle.setVelocity({0, 0});
                vehicle.setPosition({
                    vehicle.getPosition().x, platform.getPosition().y - vehicle.getSize().height
                });
                break;
            }
        }
    }

    if (vehicle.getPosition().y >= GROUND_LEVEL)
    {
        vehicle.setPosition(START_VEHICLE_POSITION);
        vehicle.setVelocity({0, 0});
        vehicle.setAcceleration({0, 0});
        return;
    }

    vehicle.setPosition({vehicle.getPosition().x + vehicle.getVelocity().x * deltaTime, vehicle.getPosition().y + vehicle.getVelocity().y * deltaTime});
}

void Game::draw()
{
    window.clear(sf::Color(0x00, 0x00, 0x00));
    window.draw(background.getBackgroundSprite());
    window.draw(vehicle.getBody());
    for (Platform &currentPlatform: platforms)
    {
        window.draw(currentPlatform.getLandscape());
        window.draw(currentPlatform.getTop());
    }
    window.display();
}
