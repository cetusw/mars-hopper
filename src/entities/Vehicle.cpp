#include "Vehicle.h"

#include <iostream>

#include "../utils/TextureLoader.h"
#include "../utils/Constants.h"

Vehicle::Vehicle() : velocity{0, 0}, acceleration{0, 0}, position{VEHICLE_START_POSITION}, size{VEHICLE_SIZE}
{
}

void Vehicle::init(const std::string &filePath)
{
    TextureLoader::loadTexture(texture, filePath);
    body.setTexture(texture);
    body.setScale(
        size.width / static_cast<float>(texture.getSize().x),
        size.height / static_cast<float>(texture.getSize().y)
    );
    body.setOrigin(0, 0);
    body.setPosition(VEHICLE_START_POSITION);
}

void Vehicle::updatePosition()
{
    reduceVelocityX();
    reduceVelocityY();
    reduceAccelerationX();
    reduceAccelerationY();
}

void Vehicle::reduceVelocityX()
{
    velocity.x += acceleration.x;
    if (velocity.x > 0)
    {
        velocity.x -= HORIZONTAL_ACCELERATION;
        if (velocity.x < 0)
        {
            velocity.x = 0;
        }
    }
    else if (velocity.x < 0)
    {
        velocity.x += HORIZONTAL_ACCELERATION;
        if (velocity.x > 0)
        {
            velocity.x = 0;
        }
    }
}

void Vehicle::reduceVelocityY()
{
    velocity.y += FREE_FALL_ACCELERATION - acceleration.y;
}

void Vehicle::reduceAccelerationX()
{
    if (acceleration.x > 0)
    {
        acceleration.x -= FREE_FALL_ACCELERATION;
        if (acceleration.x < 0)
        {
            acceleration.x = 0;
        }
    }
    else if (acceleration.x < 0)
    {
        acceleration.x += FREE_FALL_ACCELERATION;
        if (acceleration.x > 0)
        {
            acceleration.x = 0;
        }
    }
}

void Vehicle::reduceAccelerationY()
{
    if (acceleration.y > 0)
    {
        acceleration.y -= FREE_FALL_ACCELERATION;
    } else
    {
        acceleration.y = 0;
    }
}

void Vehicle::handleInput(const sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up) {
        increaseVerticalAcceleration();
    } else if (key == sf::Keyboard::Left) {
        increaseDiagonalAcceleration("left");
    } else if (key == sf::Keyboard::Right) {
        increaseDiagonalAcceleration("right");
    }
}

void Vehicle::increaseDiagonalAcceleration(const std::string &direction)
{
    if (acceleration.x >= MAX_VEHICLE_ACCELERATION || acceleration.y >= MAX_VEHICLE_ACCELERATION)
    {
        return;
    }

    if (direction == "left")
    {
        acceleration.x += VEHICLE_DIAGONAL_TRUST_X;
    }
    else if (direction == "right")
    {
        acceleration.x -= VEHICLE_DIAGONAL_TRUST_X;
    }
    acceleration.y += VEHICLE_DIAGONAL_TRUST_Y;
}

void Vehicle::increaseVerticalAcceleration()
{
    if (acceleration.x >= MAX_VEHICLE_ACCELERATION || acceleration.y >= MAX_VEHICLE_ACCELERATION)
    {
        return;
    }

    acceleration.y += VEHICLE_VERTICAL_TRUST;
}


sf::Vector2f Vehicle::getPosition() const
{
    return body.getPosition();
}

Size Vehicle::getSize() const
{
    return size;
}

sf::Sprite& Vehicle::getBody()
{
    return body;
}

sf::Vector2f Vehicle::getVelocity() const
{
    return velocity;
}

sf::Vector2f Vehicle::getAcceleration() const
{
    return acceleration;
}

void Vehicle::setPosition(const sf::Vector2f position)
{
    body.setPosition(position);
}

void Vehicle::setVelocity(const sf::Vector2f newVelocity)
{
    velocity = newVelocity;
}

void Vehicle::setAcceleration(const sf::Vector2f newAcceleration)
{
    acceleration = newAcceleration;
}



