#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr unsigned WINDOW_WIDTH = 1920;
constexpr unsigned WINDOW_HEIGHT = 1080;

constexpr float FREE_FALL_ACCELERATION = 3.7f;
constexpr float MAX_HOPPER_VELOCITY = 500.0f;

constexpr Size HOPPER_SIZE = {150.f, 150.f};
constexpr Size PLATFORM_SIZE = {400.f, 50.f};

const sf::Vector2f START_PLATFORM_POSITION = {100.f, 800.f};
const sf::Vector2f FIRST_PLATFORM_POSITION = {600.f, 400.f};
const sf::Vector2f SECOND_PLATFORM_POSITION = {1500.f, 800.f};
const sf::Vector2f START_HOPPER_POSITION = {300.f, 700.f};

#endif //CONSTANTS_H
