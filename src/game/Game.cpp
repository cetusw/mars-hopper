#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../utils/constants.h"
#include "../utils/utils.cpp"

Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mars Hopper", sf::Style::Default),
               gameState(GameState::MainMenu), timeSinceLastMeteorite(0.0f)
{
    init();
}

void Game::init()
{
    speedometer.init();
    fuelIndicator.init();
    initBackground("../assets/game-background.png");
    vehicle.init("../assets/crew-dragon.png");

    landscape.updateLandscape(LANDSCAPE_STEP, 800, 1000);

    for (int i = 0; i < 5; i++)
    {
        platforms.emplace_back();
    }

    platforms[0].init((WINDOW_WIDTH / 2) - (PLATFORM_SIZE.width / 2), platforms[0].getPlatformPositionY(WINDOW_WIDTH / 2, landscape.points),
                      "../assets/platform.png");

    std::cout << platforms[0].getPosition().y << std::endl;

    float platformPositionX = 0;
    for (int i = 1; i < 5; i++)
    {
        platformPositionX = getRandomNumber(static_cast<float>(i + 1) * (WINDOW_WIDTH / 2),
                                            static_cast<float>(i + 2) * ((WINDOW_WIDTH / 2) - PLATFORM_SIZE.width));
        platforms[i].init(
            platformPositionX,
            platforms[i].getPlatformPositionY(platformPositionX, landscape.points),
            "../assets/platform.png"
        );
    }

    for (int i = 0; i < METEORITES_AMOUNT; i++)
    {
        meteorites.emplace_back();
    }

    for (int i = 0; i < METEORITES_AMOUNT; i++)
    {
        meteorites[i].init();
    }

    loadSound(gameBuffer, "../assets/sounds/game-sound.wav");
    gameSound.setBuffer(gameBuffer);
    if (gameSound.getStatus() != sf::Sound::Playing)
    {
        gameSound.play();
    }
    gameSound.setLoop(true);
}

void Game::reset()
{
    platforms.clear();
    landscape.points.clear();
    meteorites.clear();
    init();
}

void Game::initBackground(const std::string &filePath)
{
    loadTexture(backgroundTexture, filePath);
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        WINDOW_WIDTH / backgroundSprite.getLocalBounds().width,
        WINDOW_HEIGHT / backgroundSprite.getLocalBounds().height
    );
}

void Game::run()
{
    while (window.isOpen())
    {
        if (gameState == GameState::MainMenu || gameState == GameState::Settings || gameState == GameState::Pause || gameState == GameState::GameOver)
        {
            menu.handleScreen(window, gameState);
        } else if (gameState == GameState::Start)
        {
            reset();
            handlePlaying();
        } else if (gameState == GameState::Playing)
        {
            handlePlaying();
        } else if (gameState == GameState::Exit)
        {
            window.close();
        }
    }
}

void Game::handlePlaying()
{
    float timeSinceLastUpdate = 0.0f;
    sf::Clock clock;
    while (window.isOpen() && (gameState == GameState::Playing || gameState == GameState::Start))
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
            if (event.key.code == sf::Keyboard::Escape)
            {
                gameState = GameState::Pause;
            } else
            {
                vehicle.handleInput(event.key.code);
            }
        }
    }
}

void Game::updatePlatformsPosition(const std::string &direction, std::vector<sf::Vector2f> &points)
{
    for (Platform &platform: platforms)
    {
        platform.updatePosition(direction, vehicle.getVelocity(), points);
    }
}

void Game::updateMeteoritesPosition(const std::string &direction)
{
    for (Meteorite &meteorite: meteorites)
    {
        meteorite.updatePosition(direction, vehicle.getVelocity());
    }
}

void Game::updateMapPosition()
{
    if (vehicle.getPosition().x > FREE_MOVE_BOX_RIGHT)
    {
        vehicle.setPosition({FREE_MOVE_BOX_RIGHT, vehicle.getPosition().y});
        updatePlatformsPosition("horizontal", landscape.points);
        landscape.updatePosition("horizontal", vehicle.getVelocity());
        updateMeteoritesPosition("horizontal");
    }
    if (vehicle.getPosition().x < FREE_MOVE_BOX_LEFT)
    {
        vehicle.setPosition({FREE_MOVE_BOX_LEFT, vehicle.getPosition().y});
        updatePlatformsPosition("horizontal", landscape.points);
        landscape.updatePosition("horizontal", vehicle.getVelocity());
        updateMeteoritesPosition("horizontal");
    }
    if (vehicle.getPosition().y < FREE_MOVE_BOX_TOP)
    {
        vehicle.setPosition({vehicle.getPosition().x, FREE_MOVE_BOX_TOP});
        updatePlatformsPosition("vertical", landscape.points);
        landscape.updatePosition("vertical", vehicle.getVelocity());
        updateMeteoritesPosition("vertical");
    }
    if (vehicle.getPosition().y > FREE_MOVE_BOX_BOTTOM)
    {
        vehicle.setPosition({vehicle.getPosition().x, FREE_MOVE_BOX_BOTTOM});
        updatePlatformsPosition("vertical", landscape.points);
        landscape.updatePosition("vertical", vehicle.getVelocity());
        updateMeteoritesPosition("vertical");
    }
}

void Game::addMeteorite()
{
    timeSinceLastMeteorite += TIME_STEP;

    if (timeSinceLastMeteorite < getRandomNumber(5, 10))
    {
        return;
    }

    for (Meteorite &meteorite: meteorites)
    {
        timeSinceLastMeteorite = 0.0f;
        if (!meteorite.isFalling)
        {
            meteorite.setPosition({getRandomNumber(WINDOW_WIDTH + 1000, WINDOW_WIDTH + 2000), -800});
            meteorite.setVelocity({-450, 450});
            meteorite.isFalling = true;
            break;
        }
    }
}

void Game::updateMeteoritePosition()
{
    for (Meteorite &meteorite: meteorites)
    {
        if (meteorite.isFalling)
        {
            meteorite.setPosition({
                meteorite.getPosition().x + meteorite.getVelocity().x * TIME_STEP,
                meteorite.getPosition().y + meteorite.getVelocity().y * TIME_STEP
            });
        }
    }
}

void Game::update()
{
    addMeteorite();
    updateMeteoritePosition();
    updateMapPosition();
    landscape.updateLandscape(LANDSCAPE_STEP, 800, 1000);
    for (Meteorite &meteorite: meteorites)
    {
        meteorite.updateCollidedWithLandscape(landscape.points);
        meteorite.updateCollidedWithPlatforms(platforms);
    }
    vehicle.updatePosition();
    vehicle.updateCollidedWithPlatforms(platforms);
    fuelIndicator.updateFuelIndicator(vehicle.fuel, vehicle.getPosition());
    speedometer.updateSpeedometer(vehicle.getVelocity(), vehicle.getPosition());
    vehicle.updateCollidedWithLandscape(landscape.points);
    vehicle.updateCollidedWithMeteorite(meteorites);
    if (vehicle.isCrashed)
    {
        vehicle.isCrashed = false;
        gameState = GameState::GameOver;
    }
}

void Game::draw()
{
    window.clear(sf::Color(0x00, 0x00, 0x00));

    window.draw(backgroundSprite);
    window.draw(vehicle.getBody());
    vehicle.rightThruster.draw(window);
    vehicle.leftThruster.draw(window);
    for (Platform &currentPlatform: platforms)
    {
        window.draw(currentPlatform.getBody());
    }
    for (sf::ConvexShape &landscape: landscape.landscapes)
    {
        window.draw(landscape);
    }
    for (Meteorite &currentMeteorite: meteorites)
    {
        window.draw(currentMeteorite.getBody());
    }
    window.draw(speedometer.speedText);
    window.draw(fuelIndicator.fuelText);
    window.display();
}
