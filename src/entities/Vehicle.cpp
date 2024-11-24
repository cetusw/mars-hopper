#include "Vehicle.h"

#include "Platform.h"
#include "../game/Game.h"
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
    } else if (velocity.x < 0)
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
    } else if (acceleration.x < 0)
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
    if (key == sf::Keyboard::Up)
    {
        increaseVerticalAcceleration();
    } else if (key == sf::Keyboard::Left)
    {
        increaseDiagonalAcceleration("left");
    } else if (key == sf::Keyboard::Right)
    {
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
    } else if (direction == "right")
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

bool Vehicle::collidedWithPlatform(Platform &platform) const
{
    return getPosition().y < platform.getPosition().y + platform.getSize().height &&
           getPosition().x + getSize().width > platform.getPosition().x &&
           getPosition().x < platform.getPosition().x + platform.getSize().width &&
           getPosition().y + getSize().height > platform.getPosition().y;
}

bool Vehicle::collidedWithPlatformBottom(Platform &platform) const
{
    const sf::Vector2f leftLineStart = {platform.getPosition().x, platform.getPosition().y};
    const sf::Vector2f leftLineEnd = {platform.getPosition().x - 500, platform.getPosition().y + WINDOW_HEIGHT};
    const sf::Vector2f rightLineStart = {platform.getPosition().x + platform.getSize().width, platform.getPosition().y};
    const sf::Vector2f rightLineEnd = {platform.getPosition().x + platform.getSize().width + 500, platform.getPosition().y + WINDOW_HEIGHT};

    const float leftK = (leftLineEnd.y - leftLineStart.y) / (leftLineEnd.x - leftLineStart.x);
    const float leftB = leftLineStart.y - leftK * leftLineStart.x;

    const float rightK = (rightLineEnd.y - rightLineStart.y) / (rightLineEnd.x - rightLineStart.x);
    const float rightB = rightLineStart.y - rightK * rightLineStart.x;

    return getPosition().y + getSize().height > leftK * (getPosition().x + getSize().width) + leftB &&
           getPosition().y + getSize().height > rightK * getPosition().x + rightB &&
           getPosition().y + getSize().height > platform.getPosition().y;
}

void Vehicle::updateCollidedWithPlatforms(std::vector<Platform> &platforms)
{
    for (Platform &platform: platforms)
    {
        if (collidedWithPlatform(platform))
        {
            setVelocity({0, 0});
            setPosition({
                getPosition().x, platform.getPosition().y - getSize().height
            });
            break;
        }

        if (collidedWithPlatformBottom(platform))
        {
            setPosition({VEHICLE_START_POSITION});
            setVelocity({0, 0});
            setAcceleration({0, 0});
        }
    }
}

bool Vehicle::collidedWithLandscape(const Landscape &landscape) const
{
    const sf::Vector2f leftLineStart = {landscape.getPosition().x, landscape.getPosition().y};
    const sf::Vector2f leftLineEnd = {landscape.getPosition().x - 500, landscape.getPosition().y + landscape.getSize().height};
    const sf::Vector2f rightLineStart = {landscape.getPosition().x + landscape.getSize().width, landscape.getPosition().y};
    const sf::Vector2f rightLineEnd = {
        landscape.getPosition().x + landscape.getSize().width + 500, landscape.getPosition().y + landscape.getSize().height
    };

    const float leftK = (leftLineEnd.y - leftLineStart.y) / (leftLineEnd.x - leftLineStart.x);
    const float leftB = leftLineStart.y - leftK * leftLineStart.x;

    const float rightK = (rightLineEnd.y - rightLineStart.y) / (rightLineEnd.x - rightLineStart.x);
    const float rightB = rightLineStart.y - rightK * rightLineStart.x;

    return getPosition().y + getSize().height > leftK * (getPosition().x + getSize().width) + leftB &&
           getPosition().y + getSize().height > rightK * getPosition().x + rightB &&
           getPosition().y + getSize().height > landscape.getPosition().y;
}

void Vehicle::updateCollidedWithLandscape(std::vector<Landscape> &landscapes)
{
    for (Landscape &landscape: landscapes)
    {
        if (collidedWithLandscape(landscape))
        {
            setPosition({VEHICLE_START_POSITION});
            setVelocity({0, 0});
            setAcceleration({0, 0});
        }
    }
}

sf::Vector2f Vehicle::getPosition() const
{
    return body.getPosition();
}

Size Vehicle::getSize() const
{
    return size;
}

sf::Sprite &Vehicle::getBody()
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
