#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../utils/constants.h"
#include "../utils/utils.cpp"

Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mars Hopper", sf::Style::Default),
               gameState(GameState::MainMenu), gameDifficulty(GameDifficulty::Easy), timeSinceLastMeteorite(0.0f)
{
}

void Game::init()
{
    repairKitIndicator.init();
    safetyFactor.init();
    miniMap.init();
    achievementManager.initAchievementManager();
    achievementManager.initNotification();
    passedPlatforms.init();
    speedometer.init();
    fuelIndicator.init();
    initBackground("../assets/game-background.png");
    vehicle.init("../assets/crew-dragon.png");
    initLandscape();
    initPlatforms();
    initMeteorites();
}

void Game::initLandscape()
{
    landscape.updateLandscape();

    for (int i = 0; i < 5; i++)
    {
        platforms.emplace_back();
    }
}

void Game::initPlatforms()
{
    platforms[0].init({
                          WINDOW_WIDTH / 2,
                          platforms[0].getPlatformPositionY(WINDOW_WIDTH / 2, landscape.points)
                      }, gameDifficulty);

    float platformPositionX = 0;
    for (int i = 1; i < 5; i++)
    {
        platformPositionX = getRandomNumber(static_cast<float>(i + 1) * (WINDOW_WIDTH / 2),
                                            static_cast<float>(i + 2) * ((WINDOW_WIDTH / 2) - PLATFORM_SIZE.width));
        platforms[i].init({
                              platformPositionX,
                              platforms[i].getPlatformPositionY(platformPositionX, landscape.points)
                          }, gameDifficulty);
    }
}

void Game::initMeteorites()
{
    for (int i = 0; i < METEORITES_AMOUNT; i++)
    {
        meteorites.emplace_back();
    }

    for (int i = 0; i < METEORITES_AMOUNT; i++)
    {
        meteorites[i].init();
    }
}

void Game::initSound()
{
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
    vehicle.reset();
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
        WINDOW_WIDTH / backgroundSprite.getLocalBounds().width * 1.5f,
        WINDOW_HEIGHT / backgroundSprite.getLocalBounds().height * 1.5f
    );
    backgroundSprite.setOrigin({backgroundSprite.getLocalBounds().width / 2, backgroundSprite.getLocalBounds().height / 2});
    backgroundSprite.setPosition({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2});
}

void Game::updateBackgroundPosition()
{
    backgroundSprite.setPosition({backgroundSprite.getPosition().x, backgroundSprite.getPosition().y - vehicle.getVelocity().y * TIME_STEP / 10.f});
}

void Game::run()
{
    initSound();
    while (window.isOpen())
    {
        if (gameState != GameState::Start && gameState != GameState::Playing && gameState != GameState::Exit)
        {
            menu.handleScreen(window, gameState, gameDifficulty, passedPlatforms.platformsText.getString());
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
    achievementManager.unlock("First time?");
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

void Game::updateMapPosition()
{
    if (vehicle.getPosition().x > FREE_MOVE_BOX_RIGHT)
    {
        vehicle.setPosition({FREE_MOVE_BOX_RIGHT, vehicle.getPosition().y});
        platform.updatePlatformsPosition("horizontal", landscape.points, platforms, vehicle.getVelocity(), gameDifficulty);
        landscape.updatePosition("horizontal", vehicle.getVelocity());
        meteorite.updateMeteoritesPositionRelativeToVehicle("horizontal", meteorites, vehicle.getVelocity());
    }
    if (vehicle.getPosition().x < FREE_MOVE_BOX_LEFT)
    {
        vehicle.setPosition({FREE_MOVE_BOX_LEFT, vehicle.getPosition().y});
        platform.updatePlatformsPosition("horizontal", landscape.points, platforms, vehicle.getVelocity(), gameDifficulty);
        landscape.updatePosition("horizontal", vehicle.getVelocity());
        meteorite.updateMeteoritesPositionRelativeToVehicle("horizontal", meteorites, vehicle.getVelocity());
    }
    if (vehicle.getPosition().y < FREE_MOVE_BOX_TOP)
    {
        vehicle.setPosition({vehicle.getPosition().x, FREE_MOVE_BOX_TOP});
        platform.updatePlatformsPosition("vertical", landscape.points, platforms, vehicle.getVelocity(), gameDifficulty);
        landscape.updatePosition("vertical", vehicle.getVelocity());
        meteorite.updateMeteoritesPositionRelativeToVehicle("vertical", meteorites, vehicle.getVelocity());
        updateBackgroundPosition();
    }
    if (vehicle.getPosition().y > FREE_MOVE_BOX_BOTTOM)
    {
        vehicle.setPosition({vehicle.getPosition().x, FREE_MOVE_BOX_BOTTOM});
        platform.updatePlatformsPosition("vertical", landscape.points, platforms, vehicle.getVelocity(), gameDifficulty);
        landscape.updatePosition("vertical", vehicle.getVelocity());
        meteorite.updateMeteoritesPositionRelativeToVehicle("vertical", meteorites, vehicle.getVelocity());
        updateBackgroundPosition();
    }
}

void Game::update()
{
    updateMeteorite();
    updateMapPosition();
    updateVehicle();
    landscape.updateLandscape();
    passedPlatforms.update(vehicle.getPassedPlatforms());
    fuelIndicator.updateFuelIndicator(vehicle.fuel, vehicle.getPosition());
    speedometer.updateSpeedometer(vehicle.getVelocity(), vehicle.getPosition());
    achievementManager.updateNotification();
    miniMap.updateMiniMap(vehicle);
    safetyFactor.update(vehicle);
}

void Game::updateMeteorite()
{
    meteorite.addMeteorite(meteorites, timeSinceLastMeteorite, gameDifficulty);
    meteorite.updateMeteoritePosition(meteorites);
    for (Meteorite &meteorite: meteorites)
    {
        meteorite.updateCollidedWithLandscape(landscape.points);
        meteorite.updateCollidedWithPlatforms(platforms);
    }
}

void Game::updateVehicle()
{
    vehicle.updatePosition();
    vehicle.updateCollidedWithPlatforms(platforms, achievementManager);
    if (vehicle.getRepairability())
    {
        repairKitIndicator.setDrawability(true);
    } else
    {
        repairKitIndicator.setDrawability(false);
    }
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
    for (Platform &currentPlatform: platforms)
    {
        window.draw(currentPlatform.getBody());
        if (currentPlatform.getRepairStatus())
        {
            window.draw(currentPlatform.getRepair());
        }
        if (currentPlatform.getRepairKitStatus())
        {
            window.draw(currentPlatform.getRepairKit());
        }
    }
    window.draw(vehicle.getBody());
    window.draw(safetyFactor.getBody());
    vehicle.rightEngine.draw(window);
    vehicle.leftEngine.draw(window);
    for (sf::ConvexShape &landscape: landscape.landscapes)
    {
        window.draw(landscape);
    }
    for (Meteorite &currentMeteorite: meteorites)
    {
        if (!currentMeteorite.isFalling)
        {
            continue;
        }
        window.draw(currentMeteorite.getBody());
        currentMeteorite.flame.draw(window);
    }
    window.draw(speedometer.speedText);
    window.draw(fuelIndicator.fuelText);
    window.draw(passedPlatforms.platformsText);
    achievementManager.drawAchievementNotification(window);
    miniMap.drawMiniMap(window, vehicle, platforms, landscape, meteorites);
    if (repairKitIndicator.getDrawability())
    {
        window.draw(repairKitIndicator.getSprite());
    }
    window.display();
}
