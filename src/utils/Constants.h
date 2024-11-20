#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Size.h"

constexpr float WINDOW_WIDTH = 1920.0f;
constexpr float WINDOW_HEIGHT = 1080.0f;
constexpr float FREE_MOVE_BOX_LEFT = (WINDOW_WIDTH / 5) * 2;
constexpr float FREE_MOVE_BOX_RIGHT = (WINDOW_WIDTH / 5) * 3;
constexpr float FREE_MOVE_BOX_TOP = (WINDOW_HEIGHT / 5) * 2;
constexpr float FREE_MOVE_BOX_BOTTOM = (WINDOW_HEIGHT / 5) * 3;

constexpr float FPS = 60.0f;
constexpr float TIME_STEP = 1.0f / FPS;

constexpr int GROUND_LEVEL = 900;

constexpr float FREE_FALL_ACCELERATION = 3.7f;
constexpr float HORIZONTAL_ACCELERATION = 1.0f;
constexpr float MAX_VEHICLE_ACCELERATION = 5.f;

constexpr Size VEHICLE_SIZE = {100.f, 100.f};
constexpr Size PLATFORM_SIZE = {200.f, 35.f};

const sf::Vector2f START_PLATFORM_POSITION = {100.f, 800.f};
const sf::Vector2f FIRST_PLATFORM_POSITION = {600.f, 400.f};
const sf::Vector2f SECOND_PLATFORM_POSITION = {1500.f, 800.f};
const sf::Vector2f START_VEHICLE_POSITION = {300.f, 700.f};

constexpr float VEHICLE_DIAGONAL_TRUST_X = 20.f;
constexpr float VEHICLE_DIAGONAL_TRUST_Y = 20.f;
constexpr float VEHICLE_VERTICAL_TRUST = 30.f;

#endif //CONSTANTS_H
