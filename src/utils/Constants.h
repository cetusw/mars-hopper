#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Size.h"

constexpr unsigned WINDOW_WIDTH = 1920;
constexpr unsigned WINDOW_HEIGHT = 1080;

constexpr float FPS = 60.0f;
constexpr float TIME_STEP = 1.0f / FPS;

constexpr int GROUND_LEVEL = 900;

constexpr float FREE_FALL_ACCELERATION = 3.7f;
constexpr float MAX_VEHICLE_VELOCITY = 50.f;

constexpr Size HOPPER_SIZE = {100.f, 100.f};
constexpr Size PLATFORM_SIZE = {300.f, 35.f};

const sf::Vector2f START_PLATFORM_POSITION = {100.f, 800.f};
const sf::Vector2f FIRST_PLATFORM_POSITION = {600.f, 400.f};
const sf::Vector2f SECOND_PLATFORM_POSITION = {1500.f, 800.f};
const sf::Vector2f START_HOPPER_POSITION = {300.f, 700.f};

constexpr float VEHICLE_DIAGONAL_TRUST_X = 20.f;
constexpr float VEHICLE_DIAGONAL_TRUST_Y = 20.f;
constexpr float VEHICLE_VERTICAL_TRUST = 30.f;

#endif //CONSTANTS_H
