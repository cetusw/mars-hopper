#ifndef VEHICLE_H
#define VEHICLE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Platform.h"
#include "Engine.h"
#include "Meteorite.h"
#include "../utils/Size.h"

class Vehicle
{
public:
    Vehicle();

    void init(const std::string &filePath);

    void updatePosition();

    void handleInput(sf::Keyboard::Key key);

    bool collidedWithPlatform(const Platform &platform) const;

    void updateCollidedWithPlatforms(std::vector<Platform> &platforms);

    void updateCollidedWithLandscape(const std::vector<sf::Vector2f> &points);

    bool collidedWithMeteorite(const Meteorite &meteorite) const;

    void updateCollidedWithMeteorite(std::vector<Meteorite> &meteorites);

    void updateTilt();

    void updateThrusters();

    void handleVehicleCrash();

    bool collidedWithLandscape(sf::Vector2f firstPoint, sf::Vector2f secondPoint) const;

    sf::Vector2f getPosition() const;

    sf::Vector2f getVelocity() const;

    sf::Vector2f getAcceleration() const;

    Size getSize() const;

    sf::Sprite &getBody();

    void setPosition(sf::Vector2f position);

    void setVelocity(sf::Vector2f newVelocity);

    void setAcceleration(sf::Vector2f newAcceleration);

    void setRotation(float newRotation);

    bool isCrashed;
    bool isOnPlatform;
    Engine leftThruster;
    Engine rightThruster;

private:
    void increaseDiagonalAcceleration(const std::string &direction);

    void increaseVerticalAcceleration();

    void reduceVelocityX();

    void reduceVelocityY();

    void reduceAccelerationX();

    void reduceAccelerationY();

    sf::Sprite body;
    sf::Texture texture;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f position;
    float rotation;
    Size size;
    float fuel;
};

#endif //VEHICLE_H
