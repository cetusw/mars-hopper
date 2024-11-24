#include "Game.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../utils/Constants.h"
#include "../utils/RandomGenerator.h"
#include "../utils/TextureLoader.h"

Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mars Hopper", sf::Style::Default)
{
    init();
}

void Game::init()
{
    initBackground("../assets/game-background.png");
    vehicle.init("../assets/crew-dragon.png");
    for (int i = 0; i < 5; i++)
    {
        platforms.emplace_back();
    }

    platforms[0].init((WINDOW_WIDTH / 2) - (PLATFORM_SIZE.width / 2), (WINDOW_HEIGHT / 2) + (VEHICLE_SIZE.height / 2));

    for (int i = 1; i < 5; i++)
    {
        platforms[i].init(
            RandomGenerator::getRandomNumber(static_cast<float>(i + 1) * (WINDOW_WIDTH / 2), static_cast<float>(i + 2) * ((WINDOW_WIDTH / 2) - PLATFORM_SIZE.width)),
            RandomGenerator::getRandomNumber(500, GROUND_LEVEL - platforms[0].getSize().width)
        );
    }

    for (int i = 0; i < 3; i++)
    {
        landscapes.emplace_back();
    }

    for (int i = 0; i < 3; i++)
    {
        landscapes[i].init(static_cast<float>(i) * WINDOW_WIDTH, GROUND_LEVEL);
    }
}

void Game::initBackground(const std::string &filePath)
{
    TextureLoader::loadTexture(backgroundTexture, filePath);
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        WINDOW_WIDTH / backgroundSprite.getLocalBounds().width,
        WINDOW_HEIGHT / backgroundSprite.getLocalBounds().height
    );
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
            update();
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

void Game::updatePlatformsPosition(const std::string &direction)
{
    for (Platform &platform : platforms)
    {
        platform.updatePosition(direction, vehicle.getVelocity());
    }
}

void Game::updateLandscapesPosition(const std::string &direction)
{
    for (Landscape &landscape : landscapes)
    {
        landscape.updatePosition(direction, vehicle.getVelocity());
    }
}


void Game::updateMapPosition()
{
    if (vehicle.getPosition().x > FREE_MOVE_BOX_RIGHT)
    {
        vehicle.setPosition({FREE_MOVE_BOX_RIGHT, vehicle.getPosition().y});
        updatePlatformsPosition("horizontal");
        updateLandscapesPosition("horizontal");
    }
    if (vehicle.getPosition().x < FREE_MOVE_BOX_LEFT)
    {
        vehicle.setPosition({FREE_MOVE_BOX_LEFT, vehicle.getPosition().y});
        updatePlatformsPosition("horizontal");
        updateLandscapesPosition("horizontal");
    }
    if (vehicle.getPosition().y < FREE_MOVE_BOX_TOP)
    {
        vehicle.setPosition({vehicle.getPosition().x, FREE_MOVE_BOX_TOP});
        updatePlatformsPosition("vertical");
        updateLandscapesPosition("vertical");
    }
    if (vehicle.getPosition().y > FREE_MOVE_BOX_BOTTOM)
    {
        vehicle.setPosition({vehicle.getPosition().x, FREE_MOVE_BOX_BOTTOM});
        updatePlatformsPosition("vertical");
        updateLandscapesPosition("vertical");
    }
}

void Game::update()
{
    updateMapPosition();
    vehicle.updatePosition();
    vehicle.updateCollidedWithPlatforms(platforms);
    vehicle.updateCollidedWithLandscape(landscapes);

    vehicle.setPosition(
        {vehicle.getPosition().x + vehicle.getVelocity().x * TIME_STEP, vehicle.getPosition().y + vehicle.getVelocity().y * TIME_STEP}
    );
}

void Game::draw()
{
    window.clear(sf::Color(0x00, 0x00, 0x00));
    window.draw(backgroundSprite);
    window.draw(vehicle.getBody());
    for (Platform &currentPlatform: platforms)
    {
        window.draw(currentPlatform.getLandscape());
        window.draw(currentPlatform.getTop());
    }
    for (Landscape &currentLandscape: landscapes)
    {
        window.draw(currentLandscape.getLandscape());
    }
    window.display();
}
