#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Size.h"
#include <string>

constexpr float WINDOW_WIDTH = 1920.0f;
constexpr float WINDOW_HEIGHT = 1200.0f;
constexpr float WINDOW_EXPAND = 700.0f;
const sf::Vector2f WINDOW_CENTER = {WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f};
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
constexpr float PLATFORM_OFFSET_X = 65.f;
constexpr float PLATFORM_OFFSET_Y = 78.f;
constexpr float PLATFORM_OFFSET_Y_FOR_INSERT = 80.f;

constexpr float LANDSCAPE_STEP = 100.f;
constexpr float LANDSCAPE_LEVEL_OFFSET = 20.f;
constexpr float LANDSCAPE_STEEP_PHASE_LEVEL_OFFSET = 100.f;
constexpr int LANDSCAPE_STEEP_PHASE_LENGTH = 10;
constexpr float LANDSCAPE_MIN_HEIGHT = 800.f;
constexpr float LANDSCAPE_MAX_HEIGHT = 1000.f;
constexpr float LANDSCAPE_OVERFLOW_LENGTH = 10000.f;

const sf::Vector2f START_PLATFORM_POSITION = {100.f, 800.f};
const sf::Vector2f FIRST_PLATFORM_POSITION = {600.f, 400.f};
const sf::Vector2f SECOND_PLATFORM_POSITION = {1500.f, 800.f};
const sf::Vector2f VEHICLE_START_POSITION = {(WINDOW_WIDTH / 2), -1000};

constexpr float VEHICLE_DIAGONAL_TRUST_X = 20.f;
constexpr float VEHICLE_DIAGONAL_TRUST_Y = 25.f;
constexpr float VEHICLE_VERTICAL_TRUST = 30.f;

constexpr float MAX_TILT_ANGLE = 15.f;
constexpr float RETURN_ANGLE_SPEED = 25.f;

constexpr Size ENGINE_SIZE = {500, 500};
constexpr float ENGINE_OFFSET_X = VEHICLE_SIZE.width / 4.0f;
constexpr float ENGINE_OFFSET_Y = VEHICLE_SIZE.height / 1.7f;
constexpr float ENGINE_ANGLE = 195.f;
constexpr float ENGINE_FUEL_CONSUMPTION = 5.0f;
const std::string FLAME_IMAGE = "../assets/flame.png";
constexpr int ENGINE_FLAME_END_FRAME = 30;
constexpr int ENGINE_FLAME_START_FRAME = 0;
const std::string ENGINE_SOUND = "../assets/sounds/engine.wav";

constexpr float METEORITE_RADIUS = 50.0f;
constexpr int METEORITES_AMOUNT = 10;
const sf::Vector2f METEORITE_RIGHT_VELOCITY = {-450, 450};
const sf::Vector2f METEORITE_LEFT_VELOCITY = {450, 450};
constexpr float METEORITE_ANGEL = 45.0f;
constexpr Size METEORITE_FLAME_SIZE = {3000, 3000};
constexpr float METEORITE_FLAME_OFFSET = 150.0f;

const std::string BOLD_FONT = "../assets/fonts/SpaceMono-Bold.ttf";
const std::string REGULAR_FONT = "../assets/fonts/SpaceMono-Regular.ttf";

constexpr float TITLE_FONT_SIZE = 85.0f;
constexpr float SUBTITLE_FONT_SIZE = 50.0f;

const std::vector<std::string> OPTIONS_MAIN_MENU = {"Start", "Settings", "Achievements", "Exit"};
const std::vector<std::string> OPTIONS_SETTINGS = {"Difficulty", "Back"};
const std::vector<std::string> OPTIONS_GAME_OVER = {"Restart", "Back to Main Menu"};
const std::vector<std::string> OPTIONS_PAUSE = {"Back to game", "Restart", "Back to Main Menu"};
const std::vector<std::string> OPTIONS_DIFFICULTY = {"Easy", "Normal", "Hard", "Back"};

const sf::Vector2f TITLE_POSITION_LEFT = {300.f, 200.f};

const sf::Vector2f PASSED_PLATFORMS_POSITION = {50.f, WINDOW_HEIGHT - 150.f};

const sf::Vector2f ACHIEVEMENT_SIZE = {600, 150};
const sf::Vector2f ACHIEVEMENT_START_POSITION = {WINDOW_WIDTH + ACHIEVEMENT_SIZE.x / 2, ACHIEVEMENT_SIZE.y};
const sf::Vector2f ACHIEVEMENT_END_POSITION = {WINDOW_WIDTH - ACHIEVEMENT_SIZE.x / 2, ACHIEVEMENT_SIZE.y};
constexpr float ACHIEVEMENT_SHOW_TIME = 5.0f;
constexpr float ACHIEVEMENT_ANIMATION_SPEED = 20.0f;
constexpr float ACHIEVEMENT_FONT_SIZE = 50.0f;
constexpr float ACHIEVEMENT_ANIMATION_ACCELERATION = 1.05f;

constexpr float FUEL_INDICATOR_FONT_SIZE = 30.0f;
constexpr float MIN_FUEL_AMOUNT = 30.0f;

const std::string ACHIEVEMENTS_FILE = "../achievements.txt";

const std::string MENU_BACKGROUND_IMAGE = "../assets/menu-background.png";

constexpr float MINIMAP_SCALE = 0.2f;

const sf::Vector2f SAFETY_FACTOR_SIZE = {30, 10};
constexpr float SAFETY_FACTOR_OFFSET_Y = 15.0f;

constexpr float FRAME_WIDTH = 128;
constexpr float FRAME_HEIGHT = 126;

const std::string REPAIR_TEXTURE_PATH = "../assets/repair.png";
constexpr Size REPAIR_SIZE = {40, 40};
constexpr float REPAIR_OFFSET = 60.f;

const std::string REPAIR_KIT_TEXTURE_PATH = "../assets/repair-kit.png";
constexpr Size REPAIR_KIT_SIZE  = {40, 40};
constexpr int REPAIR_KITS_AMOUNT = 3;
constexpr float REPAIR_KIT_OFFSET = 108.0f;

const std::string PLATFORM_TEXTURE_PATH = "../assets/platform.png";

constexpr Size REPAIR_KIT_INDICATOR_SIZE = {200, 200};

constexpr int MAX_SAFETY_FACTOR_AMOUNT = 3;
constexpr float MAX_FUEL_AMOUNT = 100.0f;

#endif //CONSTANTS_H
