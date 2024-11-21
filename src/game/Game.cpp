#include "Game.h"

#include <iostream>

#include "../utils/Constants.h"
#include "../utils/RandomGenerator.h"
#include "../utils/TextureLoader.h"

Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mars Hopper", sf::Style::Default)
{
    init();
}

void Game::init()
{
    background.init("../assets/game-background.png");
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

bool Game::collidedWithPlatformBottom(const Vehicle &vehicle, const Platform &platform)
{
    // слишком много логики в Game и мало в классах
    const sf::Vector2f leftLineStart = {platform.getPosition().x, platform.getPosition().y};
    const sf::Vector2f leftLineEnd = {platform.getPosition().x - 500, platform.getPosition().y + WINDOW_HEIGHT};
    const sf::Vector2f rightLineStart = {platform.getPosition().x + platform.getSize().width, platform.getPosition().y};
    const sf::Vector2f rightLineEnd = {platform.getPosition().x + platform.getSize().width + 500, platform.getPosition().y + WINDOW_HEIGHT};

    const float leftK = (leftLineEnd.y - leftLineStart.y) / (leftLineEnd.x - leftLineStart.x);
    const float leftB = leftLineStart.y - leftK * leftLineStart.x;

    const float rightK = (rightLineEnd.y - rightLineStart.y) / (rightLineEnd.x - rightLineStart.x);
    const float rightB = rightLineStart.y - rightK * rightLineStart.x;

    return vehicle.getPosition().y + vehicle.getSize().height > leftK * (vehicle.getPosition().x + vehicle.getSize().width) + leftB &&
           vehicle.getPosition().y + vehicle.getSize().height > rightK * vehicle.getPosition().x + rightB &&
           vehicle.getPosition().y + vehicle.getSize().height > platform.getPosition().y;
}

bool Game::collidedWithPlatform(const Vehicle &vehicle, const Platform &platform)
{
    return vehicle.getPosition().y < platform.getPosition().y + platform.getSize().height &&
           vehicle.getPosition().x + vehicle.getSize().width > platform.getPosition().x &&
           vehicle.getPosition().x < platform.getPosition().x + platform.getSize().width &&
           vehicle.getPosition().y + vehicle.getSize().height > platform.getPosition().y;
}

bool Game::collidedWithLandscape(const Vehicle &vehicle, const Landscape &landscape)
{
    const sf::Vector2f leftLineStart = {landscape.getPosition().x, landscape.getPosition().y};
    const sf::Vector2f leftLineEnd = {landscape.getPosition().x - 500, landscape.getPosition().y + landscape.getSize().height};
    const sf::Vector2f rightLineStart = {landscape.getPosition().x + landscape.getSize().width, landscape.getPosition().y};
    const sf::Vector2f rightLineEnd = {
        landscape.getPosition().x + landscape.getSize().width + 500, landscape.getPosition().y + landscape.getSize().height
    };

    const float leftK = (leftLineEnd.y - leftLineStart.y) / (leftLineEnd.x - leftLineStart.x);
    const float leftB = leftLineStart.y - leftK * leftLineStart.x;

    const float rightK = (rightLineEnd.y - rightLineStart.y) / (rightLineEnd.x - rightLineStart.x);
    const float rightB = rightLineStart.y - rightK * rightLineStart.x;

    return vehicle.getPosition().y + vehicle.getSize().height > leftK * (vehicle.getPosition().x + vehicle.getSize().width) + leftB &&
           vehicle.getPosition().y + vehicle.getSize().height > rightK * vehicle.getPosition().x + rightB &&
           vehicle.getPosition().y + vehicle.getSize().height > landscape.getPosition().y;
}

void Game::movePlatformForward(Platform &platform)
{
    if (platform.getPosition().x + platform.getSize().width < -WINDOW_WIDTH - 500)
    {
        platform.setPosition(
            WINDOW_WIDTH + 500,
            RandomGenerator::getRandomNumber(200, GROUND_LEVEL)
        );
    }
}

void Game::moveLandscapeForward(Landscape &landscape)
{
    if (landscape.getPosition().x + landscape.getSize().width < -WINDOW_WIDTH)
    {
        landscape.setPosition(
            WINDOW_WIDTH,
            GROUND_LEVEL
        );
    }
}

void Game::updatePlatformsPosition(const std::string direction)
{
    if (direction == "horizontal")
    {
        for (Platform &platform: platforms)
        { // если вынести цикл уровнем выше, то получится один цикл и один вызов move
            platform.setPosition(platform.getPosition().x - vehicle.getVelocity().x * TIME_STEP, platform.getPosition().y);
            movePlatformForward(platform);
        }
    } else if (direction == "vertical")
    {
        for (Platform &platform: platforms)
        {
            platform.setPosition(platform.getPosition().x, platform.getPosition().y - vehicle.getVelocity().y * TIME_STEP);
            movePlatformForward(platform);
        }
    }
}

void Game::updateLandscapesPosition(const std::string direction)
{
    if (direction == "horizontal")
    {
        for (Landscape &landscape: landscapes)
        {
            landscape.setPosition(landscape.getPosition().x - vehicle.getVelocity().x * TIME_STEP, landscape.getPosition().y);
            moveLandscapeForward(landscape);
        }
    } else if (direction == "vertical")
    {
        for (Landscape &landscape: landscapes)
        {
            landscape.setPosition(landscape.getPosition().x, landscape.getPosition().y - vehicle.getVelocity().y * TIME_STEP);
            moveLandscapeForward(landscape);
        }
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

void Game::updateCollidedWithPlatforms()
{
    for (Platform &platform: platforms)
    {
        if (collidedWithPlatform(vehicle, platform))
        {
            vehicle.setVelocity({0, 0});
            vehicle.setPosition({
                vehicle.getPosition().x, platform.getPosition().y - vehicle.getSize().height
            });
            break;
        }

        if (collidedWithPlatformBottom(vehicle, platform))
        {
            vehicle.setPosition({VEHICLE_START_POSITION});
            vehicle.setVelocity({0, 0});
            vehicle.setAcceleration({0, 0});
        }
    }
}

void Game::updateCollidedWithLandscape()
{
    for (Landscape &landscape: landscapes)
    {
        if (collidedWithLandscape(vehicle, landscape))
        {
            vehicle.setPosition({VEHICLE_START_POSITION});
            vehicle.setVelocity({0, 0});
            vehicle.setAcceleration({0, 0});
        }
    }
}

void Game::update()
{
    updateMapPosition();
    vehicle.updatePosition();
    updateCollidedWithPlatforms();
    updateCollidedWithLandscape();

    vehicle.setPosition(
        {vehicle.getPosition().x + vehicle.getVelocity().x * TIME_STEP, vehicle.getPosition().y + vehicle.getVelocity().y * TIME_STEP}
    );
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
    for (Landscape &currentLandscape: landscapes)
    {
        window.draw(currentLandscape.getLandscape());
    }
    window.display();
}
