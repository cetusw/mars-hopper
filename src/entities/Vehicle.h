#ifndef VEHICLE_H
#define VEHICLE_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Platform.h"
#include "Landscape.h"
#include "../utils/Size.h"


class Vehicle {
public:
    Vehicle();
    void init(const std::string &filePath);
    void updatePosition();
    void handleInput(sf::Keyboard::Key key);

    bool collidedWithPlatform(Platform &platform) const;
    void updateCollidedWithPlatforms(std::vector<Platform> &platforms);
    bool collidedWithPlatformBottom(Platform &platform) const;
    void updateCollidedWithLandscape(std::vector<Landscape> &landscapes);
    bool collidedWithLandscape(const Landscape &landscape) const;

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    sf::Vector2f getAcceleration() const;
    Size getSize() const;
    sf::Sprite& getBody();
    void setPosition(sf::Vector2f position);
    void setVelocity(sf::Vector2f newVelocity);
    void setAcceleration(sf::Vector2f newAcceleration);

private:
    sf::Sprite body;
    sf::Texture texture;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f position;
    Size size;

    void increaseDiagonalAcceleration(const std::string &direction);
    void increaseVerticalAcceleration();
    void reduceVelocityX();
    void reduceVelocityY();
    void reduceAccelerationX();
    void reduceAccelerationY();
};

#endif //VEHICLE_H
