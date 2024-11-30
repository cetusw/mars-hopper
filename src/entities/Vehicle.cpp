#include "Vehicle.h"

#include <iostream>

#include "Platform.h"
#include "../game/Game.h"
#include "../utils/constants.h"

extern float toRadians(float degrees);
extern void loadTexture(sf::Texture &texture, const std::string &filePath);

Vehicle::Vehicle() : velocity{0, 0}, acceleration{0, 0}, position{VEHICLE_START_POSITION}, rotation(0), size{VEHICLE_SIZE}, fuel(100)
{
}

void Vehicle::init(const std::string &filePath)
{
    loadTexture(texture, filePath);
    body.setTexture(texture);
    body.setScale(
        size.width / static_cast<float>(texture.getSize().x),
        size.height / static_cast<float>(texture.getSize().y)
    );
    body.setOrigin(
        static_cast<float>(texture.getSize().x) / 2.0f,
        static_cast<float>(texture.getSize().y) / 2.0f
    );
    body.setPosition(VEHICLE_START_POSITION);

    leftThruster.init("../assets/flame.png");
    leftThruster.setRotation(15.0f);
    rightThruster.init("../assets/flame.png");
    rightThruster.setRotation(-15.0f);
}

void Vehicle::updatePosition()
{
    reduceVelocityX();
    reduceVelocityY();
    reduceAccelerationX();
    reduceAccelerationY();
    updateTilt();
    updateThrusters();
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
    if (fuel <= 0)
    {
        return;
    }

    if (key == sf::Keyboard::Up)
    {
        fuel -= 10.0f;
        leftThruster.thrust();
        rightThruster.thrust();
        increaseVerticalAcceleration();
    }

    if (key == sf::Keyboard::Left)
    {
        fuel -= 5.0f;
        increaseDiagonalAcceleration("left");
        leftThruster.thrust();
    }

    if (key == sf::Keyboard::Right)
    {
        fuel -= 5.0f;
        increaseDiagonalAcceleration("right");
        rightThruster.thrust();
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

bool Vehicle::collidedWithPlatform(const Platform &platform) const
{
    return getPosition().y + getSize().height / 2.0f > platform.getPosition().y &&
           getPosition().x + getSize().width / 2.0f > platform.getPosition().x &&
           getPosition().x - getSize().width / 2.0f < platform.getPosition().x + platform.getSize().width &&
           getPosition().y - getSize().height / 2.0f < platform.getPosition().y + platform.getSize().height;
}

bool Vehicle::collidedWithPlatformBottom(const Platform &platform) const
{
    const sf::Vector2f leftLineStart = {platform.getPosition().x, platform.getPosition().y};
    const sf::Vector2f leftLineEnd = {platform.getPosition().x - 500, platform.getPosition().y + WINDOW_HEIGHT};
    const sf::Vector2f rightLineStart = {platform.getPosition().x + platform.getSize().width, platform.getPosition().y};
    const sf::Vector2f rightLineEnd = {platform.getPosition().x + platform.getSize().width + 500, platform.getPosition().y + WINDOW_HEIGHT};

    const float leftK = (leftLineEnd.y - leftLineStart.y) / (leftLineEnd.x - leftLineStart.x);
    const float leftB = leftLineStart.y - leftK * leftLineStart.x;

    const float rightK = (rightLineEnd.y - rightLineStart.y) / (rightLineEnd.x - rightLineStart.x);
    const float rightB = rightLineStart.y - rightK * rightLineStart.x;

    return getPosition().y + getSize().height / 2.0f > leftK * (getPosition().x + getSize().width / 2.0f) + leftB &&
           getPosition().y + getSize().height / 2.0f > rightK * (getPosition().x - getSize().width / 2.0f) + rightB &&
           getPosition().y + getSize().height / 2.0f > platform.getPosition().y;
}

void Vehicle::updateCollidedWithPlatforms(std::vector<Platform> &platforms)
{
    for (Platform &platform: platforms)
    {
        if (collidedWithPlatform(platform))
        {
            fuel = 100.f;
            setVelocity({0, 0});
            setPosition({
                getPosition().x,
                platform.getPosition().y - getSize().height / 2.0f
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

    return getPosition().y + getSize().height / 2.0f > leftK * (getPosition().x + getSize().width / 2.0f) + leftB &&
           getPosition().y + getSize().height / 2.0f > rightK * (getPosition().x - getSize().width / 2.0f) + rightB &&
           getPosition().y + getSize().height / 2.0f > landscape.getPosition().y;
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

void Vehicle::updateTilt()
{
    if (velocity.x > 0)
    {
        rotation += std::min(velocity.x * TIME_STEP, MAX_TILT_ANGLE - rotation);
    }
    else if (velocity.x < 0)
    {
        rotation += std::max(velocity.x * TIME_STEP, -MAX_TILT_ANGLE - rotation);
    }
    else
    {
        if (rotation > 0)
        {
            rotation = std::max(rotation - RETURN_ANGLE_SPEED * TIME_STEP, 0.f);
        }
        else if (rotation < 0)
        {
            rotation = std::min(rotation + RETURN_ANGLE_SPEED * TIME_STEP, 0.f);
        }
    }

    body.setRotation(rotation);
}

void Vehicle::updateThrusters()
{
    leftThruster.update();
    rightThruster.update();
    leftThruster.rotation = rotation + THRUSTER_ANGLE;
    rightThruster.rotation = rotation - THRUSTER_ANGLE;
    leftThruster.updateThrusterPosition({THRUSTER_OFFSET_X, -THRUSTER_OFFSET_Y}, getPosition());
    rightThruster.updateThrusterPosition({-THRUSTER_OFFSET_X, -THRUSTER_OFFSET_Y}, getPosition());
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
