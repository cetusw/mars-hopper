#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Size.h"
#include "../entities/Vehicle.h"
#include <string>

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
constexpr float MAX_AllOWED_SPEED = 250.f;

constexpr Size VEHICLE_SIZE = {100.f, 100.f};
constexpr Size PLATFORM_SIZE = {286.f, 500.f};
constexpr float PLATFORM_OFFSET_X = 50.f;
constexpr float PLATFORM_OFFSET_Y = 270.f;

constexpr float LANDSCAPE_STEP = 100.f;

const sf::Vector2f START_PLATFORM_POSITION = {100.f, 800.f};
const sf::Vector2f FIRST_PLATFORM_POSITION = {600.f, 400.f};
const sf::Vector2f SECOND_PLATFORM_POSITION = {1500.f, 800.f};
const sf::Vector2f VEHICLE_START_POSITION = {(WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2) - 1000};

constexpr float VEHICLE_DIAGONAL_TRUST_X = 20.f;
constexpr float VEHICLE_DIAGONAL_TRUST_Y = 25.f;
constexpr float VEHICLE_VERTICAL_TRUST = 30.f;

constexpr float MAX_TILT_ANGLE = 15.f;
constexpr float RETURN_ANGLE_SPEED = 25.f;

constexpr float THRUSTER_OFFSET_X = VEHICLE_SIZE.width / 4.0f;
constexpr float THRUSTER_OFFSET_Y = VEHICLE_SIZE.height / 1.7f;
constexpr float THRUSTER_ANGLE = 195.f;
constexpr float THRUSTER_FUEL_CONSUMPTION = 5.0f;

constexpr float METEORITE_RADIUS = 50.0f;
constexpr int METEORITES_AMOUNT = 3;

const std::string BOLD_FONT = "../assets/fonts/SpaceMono-Bold.ttf";
const std::string REGULAR_FONT = "../assets/fonts/SpaceMono-Regular.ttf";

const std::vector<std::string> OPTIONS_MAIN_MENU = {"Start", "Settings", "Exit"};
const std::vector<std::string> OPTIONS_SETTINGS = {"Volume", "Back"};
const std::vector<std::string> OPTIONS_GAME_OVER = {"Restart", "Back to Main Menu"};
const std::vector<std::string> OPTIONS_PAUSE = {"Restart", "Back to Main Menu"};

const sf::Vector2f TITLE_POSITION_LEFT = {300.f, 200.f};



#endif //CONSTANTS_H
