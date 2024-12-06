#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>
#include "../utils/Size.h"

class Platform
{
public:
    Platform();

    void init(float x, float y, const std::string &filePath);

    void moveForward(std::vector<sf::Vector2f> &points);

    void updatePosition(const std::string &direction, const sf::Vector2f &velocity, std::vector<sf::Vector2f> &points);

    float getPlatformPositionY(float x, std::vector<sf::Vector2f> &points);

    sf::Vector2f getPosition() const;

    Size getSize() const;

    sf::Sprite getBody();

    void setPosition(float x, float y);

private:
    sf::Sprite body;
    sf::Texture texture;
    Size size;
};

#endif //PLATFORM_H
