// #include <iostream>
// #include <random>
//
// #include <SFML/Graphics.hpp>
//
// struct Size
// {
//     float width;
//     float height;
// };
//
// constexpr unsigned WINDOW_WIDTH = 1920;
// constexpr unsigned WINDOW_HEIGHT = 1080;
//
// constexpr float FREE_FALL_ACCELERATION = 3.7f;
// constexpr float MAX_HOPPER_VELOCITY = 500.0f;
// constexpr Size HOPPER_SIZE = {150.f, 150.f};
// constexpr Size PLATFORM_SIZE = {400.f, 50.f};
// const sf::Vector2f START_PLATFORM_POSITION = {100.f, 800.f};
// const sf::Vector2f FIRST_PLATFORM_POSITION = {600.f, 400.f};
// const sf::Vector2f SECOND_PLATFORM_POSITION = {1500.f, 800.f};
// const sf::Vector2f START_HOPPER_POSITION = {300.f, 700.f};
//
// struct Hopper
// {
//     sf::Sprite body;
//     sf::Vector2f velocity = {0, 0};
//     sf::Vector2f acceleration = {0, 0};
//     sf::Vector2f position;
//     Size size = HOPPER_SIZE;
// };
//
// struct Platform
// {
//     sf::ConvexShape body;
//     sf::Vector2f position;
//     Size size = PLATFORM_SIZE;
// };
//
// float getRandomNumber(const float min, const float max)
// {
//     static std::random_device rd;
//     static std::mt19937 generator(rd());
//     std::uniform_real_distribution distribution(min, max);
//
//     return distribution(generator);
// }
//
// void loadTexture(sf::Texture &texture, const std::string &filePath)
// {
//     if (!texture.loadFromFile(filePath))
//     {
//         std::cerr << "Не удалось открыть файл" << std::endl;
//     }
// }
//
// sf::Vector2f calculateHopperSize(const Hopper &hopper, const sf::Texture &texture)
// {
//     const sf::Vector2u textureSize = texture.getSize();
//     return {
//         hopper.size.width / static_cast<float>(textureSize.x),
//         hopper.size.height / static_cast<float>(textureSize.y)
//     };
// }
//
// void initHopper(Hopper &hopper, sf::Texture &texture, const std::string &filePath)
// {
//     loadTexture(texture, filePath);
//
//     const sf::Vector2f hopperSize = calculateHopperSize(hopper, texture);
//
//     hopper.body.setScale(hopperSize);
//     hopper.position = START_HOPPER_POSITION;
//     hopper.body.setTexture(texture);
//     hopper.body.setOrigin(sf::Vector2f(0, 0));
// }
//
// void initPlatform(Platform &platform, float x, float y)
// {
//     platform.position = {x, y};
//     platform.body.setPosition(platform.position);
//
//     platform.body.setPointCount(4);
//     platform.body.setPoint(0, {0, 0});
//     platform.body.setPoint(1, {platform.size.width, 0});
//     platform.body.setPoint(2, {platform.size.width, platform.size.height});
//     platform.body.setPoint(3, {0, platform.size.height});
//
//     platform.body.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
// }
//
// void initPlatforms(std::vector<Platform> &platform)
// {
//     Platform startPlatform, platform1, platform2;
//     platform.emplace_back(platform1);
//     platform.emplace_back(platform2);
//     initPlatform(platform[0], FIRST_PLATFORM_POSITION.x, FIRST_PLATFORM_POSITION.y);
//     initPlatform(platform[1], SECOND_PLATFORM_POSITION.x, SECOND_PLATFORM_POSITION.y);
// }
//
// void reduceAccelerationX(Hopper &hopper)
// {
//     if (hopper.acceleration.x > 0)
//     {
//         hopper.acceleration.x -= FREE_FALL_ACCELERATION;
//         if (hopper.acceleration.x < 0)
//         {
//             hopper.acceleration.x = 0;
//         }
//     } else if (hopper.acceleration.x < 0)
//     {
//         hopper.acceleration.x += FREE_FALL_ACCELERATION;
//         if (hopper.acceleration.x > 0)
//         {
//             hopper.acceleration.x = 0;
//         }
//     }
// }
//
// void reduceAccelerationY(Hopper &hopper)
// {
//     if (hopper.acceleration.y > 0)
//     {
//         hopper.acceleration.y -= FREE_FALL_ACCELERATION;
//     } else
//     {
//         hopper.acceleration.y = 0;
//     }
// }
//
// bool collidedWithPlatform(const Hopper &hopper, const Platform &platform)
// {
//     return !(hopper.position.y >= platform.position.y + platform.size.height ||
//              (hopper.position.x + hopper.size.width <= platform.position.x ||
//               hopper.position.x >= platform.position.x + platform.size.width ||
//               hopper.position.y + hopper.size.height <= platform.position.y));
// }
//
// void updateCollide(std::vector<Platform> &platforms, Hopper &hopper, const float deltaTime)
// {
//     bool collided = false;
//
//     for (Platform &currentPlatform: platforms)
//     {
//         if (collidedWithPlatform(hopper, currentPlatform))
//         {
//             if (hopper.position.y + hopper.size.height <= currentPlatform.position.y + currentPlatform.size.height)
//             {
//                 hopper.position.y = currentPlatform.position.y - hopper.size.height;
//                 hopper.velocity = {0, 0};
//                 collided = true;
//                 break;
//             }
//         }
//     }
//
//     if (!collided)
//     {
//         hopper.position += hopper.velocity * deltaTime;
//     }
//
//     if (hopper.position.y > WINDOW_HEIGHT)
//     {
//         hopper.position = START_HOPPER_POSITION;
//         hopper.velocity = {0, 0};
//         hopper.acceleration = {0, 0};
//     }
// }
//
// void updateHopperElements(Hopper &hopper)
// {
//     hopper.body.setPosition(hopper.position);
// }
//
// void updateHopperPosition(const float deltaTime, Hopper &hopper, std::vector<Platform> &platforms)
// {
//     hopper.velocity.x += hopper.acceleration.x;
//     hopper.velocity.y += FREE_FALL_ACCELERATION - hopper.acceleration.y;
//
//     reduceAccelerationX(hopper);
//     reduceAccelerationY(hopper);
//
//     updateCollide(platforms, hopper, deltaTime);
//
//     updateHopperElements(hopper);
// }
//
// void pollEvents(sf::RenderWindow &window, Hopper &hopper)
// {
//     sf::Event event;
//     while (window.pollEvent(event))
//     {
//         switch (event.type)
//         {
//             case sf::Event::Closed:
//                 window.close();
//                 break;
//             case sf::Event::KeyPressed:
//                 if (event.key.code == sf::Keyboard::Up)
//                 {
//                     hopper.acceleration.y += 70.0f;
//                 } else if (event.key.code == sf::Keyboard::Right)
//                 {
//                     hopper.acceleration.x += 30.0f;
//                     hopper.acceleration.y += 70.0f;
//                 } else if (event.key.code == sf::Keyboard::Left)
//                 {
//                     hopper.acceleration.x += -30.0f;
//                     hopper.acceleration.y += 70.0f;
//                 }
//                 break;
//             default:
//                 break;
//         }
//     }
// }
//
// void redrawFrame(sf::RenderWindow &window, const Hopper &hopper, std::vector<Platform> &platforms)
// {
//     window.clear(sf::Color(0x00, 0x00, 0x00));
//     window.draw(hopper.body);
//     for (Platform &onePlatform: platforms)
//     {
//         window.draw(onePlatform.body);
//     }
//     window.display();
// }
//
// int main()
// {
//     sf::Clock clock;
//
//     sf::ContextSettings settings;
//     settings.antialiasingLevel = 8;
//     sf::RenderWindow window(
//         sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
//         "Mars Hopper", sf::Style::Default, settings);
//
//     Hopper hopper;
//     std::vector<Platform> platforms;
//     Platform startPlatform;
//
//     sf::Texture hopperTexture;
//     initHopper(hopper, hopperTexture, "../assets/crew-dragon.png");
//     initPlatforms(platforms);
//     initPlatform(startPlatform, START_PLATFORM_POSITION.x, START_PLATFORM_POSITION.y);
//     platforms.emplace_back(startPlatform);
//
//     while (window.isOpen())
//     {
//         const float deltaTime = clock.restart().asSeconds();
//         pollEvents(window, hopper);
//         updateHopperPosition(deltaTime, hopper, platforms);
//         redrawFrame(window, hopper, platforms);
//     }
// }
#include "src/game/Game.h"

int main() {
    Game game;
    game.run();
    return 0;
}
