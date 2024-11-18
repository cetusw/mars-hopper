#include "Hopper.h"

#include <iostream>

#include "../utils/TextureLoader.h"
#include "../utils/Constants.h"

Hopper::Hopper() : velocity{0, 0}, acceleration{0, 0}, position{400, 300}, size{HOPPER_SIZE}
{
}

void Hopper::init(const std::string &filePath)
{
    TextureLoader::loadTexture(texture, filePath);
    body.setTexture(texture);
    body.setScale(
        size.width / static_cast<float>(texture.getSize().x),
        size.height / static_cast<float>(texture.getSize().y)
    );
    body.setOrigin(0, 0);
    body.setPosition(START_HOPPER_POSITION);
}

void Hopper::updatePosition()
{
    velocity.x += acceleration.x;
    velocity.y += FREE_FALL_ACCELERATION - acceleration.y;
    reduceAccelerationX();
    reduceAccelerationY();
}

void Hopper::reduceAccelerationX()
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

void Hopper::reduceAccelerationY()
{
    if (acceleration.y > 0)
    {
        acceleration.y -= FREE_FALL_ACCELERATION;
    } else
    {
        acceleration.y = 0;
    }
}

void Hopper::handleInput(const sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up) {
        acceleration.y += VEHICLE_TRUST_Y;
    } else if (key == sf::Keyboard::Right) {
        acceleration.x += VEHICLE_TRUST_X;
        acceleration.y += 25.f;
    } else if (key == sf::Keyboard::Left) {
        acceleration.x -= VEHICLE_TRUST_X;
        acceleration.y += 25.f;
    }
}

sf::Vector2f Hopper::getPosition() const
{
    return body.getPosition();
}

Size Hopper::getSize() const
{
    return size;
}

sf::Sprite& Hopper::getBody()
{
    return body;
}

sf::Vector2f Hopper::getVelocity() const
{
    return velocity;
}

sf::Vector2f Hopper::getAcceleration() const
{
    return acceleration;
}

void Hopper::setPosition(const sf::Vector2f position)
{
    body.setPosition(position);
}

void Hopper::setVelocity(const sf::Vector2f newVelocity)
{
    velocity = newVelocity;
}

void Hopper::setAcceleration(const sf::Vector2f newAcceleration)
{
    acceleration = newAcceleration;
}



