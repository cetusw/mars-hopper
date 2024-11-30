#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Size.h"
#include "../entities/Vehicle.h"

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
const sf::Vector2f VEHICLE_START_POSITION = {(WINDOW_WIDTH / 2) - (VEHICLE_SIZE.width / 2), (WINDOW_HEIGHT / 2) - (VEHICLE_SIZE.height / 2) - 100};

constexpr float VEHICLE_DIAGONAL_TRUST_X = 20.f;
constexpr float VEHICLE_DIAGONAL_TRUST_Y = 20.f;
constexpr float VEHICLE_VERTICAL_TRUST = 30.f;

constexpr float MAX_TILT_ANGLE = 15.f;
constexpr float RETURN_ANGLE_SPEED = 25.f;

constexpr float THRUSTER_OFFSET_X = VEHICLE_SIZE.width / 4.0f;
constexpr float THRUSTER_OFFSET_Y = VEHICLE_SIZE.height / 1.7f;
constexpr float THRUSTER_ANGLE = 195.f;

#endif //CONSTANTS_H