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

    void updatePlatformsPosition(const std::string &direction, std::vector<sf::Vector2f> &points, std::vector<Platform> &platforms,
                                        sf::Vector2f velocity);

    float getPlatformPositionY(float x, std::vector<sf::Vector2f> &points);

    sf::Vector2f getPosition() const;

    Size getSize() const;

    sf::Sprite getBody();

    int getId() const;

    void setPosition(float x, float y);

    void setId();

private:
    int id;
    static int lastId;
    sf::Sprite body;
    sf::Texture texture;
    Size size;
};

#endif //PLATFORM_H
