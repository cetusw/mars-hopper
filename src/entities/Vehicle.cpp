#include "Vehicle.h"
#include <iostream>
#include "../utils/utils.cpp"
#include "Platform.h"
#include "../game/Game.h"
#include "../utils/constants.h"

Vehicle::Vehicle() : isCrashed(false), isOnPlatform(false), velocity{0, 0}, acceleration{0, 0}, position{VEHICLE_START_POSITION}, rotation(0),
                     size{VEHICLE_SIZE}, fuel(100)
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
    body.setRotation(0);

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

    isOnPlatform = false;

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
    return getPosition().y + getSize().height / 2.0f > platform.getPosition().y + PLATFORM_OFFSET_Y &&
           getPosition().x + getSize().width / 2.0f > platform.getPosition().x + PLATFORM_OFFSET_X &&
           getPosition().x - getSize().width / 2.0f < platform.getPosition().x + platform.getSize().width - PLATFORM_OFFSET_X &&
           getPosition().y - getSize().height / 2.0f < platform.getPosition().y + PLATFORM_OFFSET_Y + platform.getSize().height;
}

void Vehicle::updateCollidedWithPlatforms(std::vector<Platform> &platforms)
{
    for (Platform &platform: platforms)
    {
        if (collidedWithPlatform(platform))
        {
            fuel = 100.f;
            isOnPlatform = true;
            setVelocity({0, 0});
            setPosition({
                getPosition().x,
                platform.getPosition().y - getSize().height / 2.0f + 270
            });
            break;
        }
    }
}

bool Vehicle::collidedWithLandscape(const sf::Vector2f firstPoint, const sf::Vector2f secondPoint) const
{
    if (secondPoint.x == firstPoint.x)
    {
        return getPosition().x + getSize().width / 2.0f > firstPoint.x &&
               getPosition().x - getSize().width / 2.0f < firstPoint.x &&
               getPosition().y + getSize().height / 2.0f > std::min(firstPoint.y, secondPoint.y) &&
               getPosition().y - getSize().height / 2.0f < std::max(firstPoint.y, secondPoint.y);
    }

    const float k = (secondPoint.y - firstPoint.y) / (secondPoint.x - firstPoint.x);
    const float b = firstPoint.y - k * firstPoint.x;

    const float vehicleCenterX = getPosition().x;
    const float vehicleBottomY = getPosition().y + getSize().height / 2.0f;
    const float vehicleRightX = getPosition().x + getSize().width / 2.0f;
    const float vehicleLeftX = getPosition().x - getSize().width / 2.0f;

    return vehicleBottomY > k * vehicleCenterX + b &&
           vehicleRightX > firstPoint.x &&
           vehicleLeftX < secondPoint.x;
}

void Vehicle::updateCollidedWithLandscape(const std::vector<sf::Vector2f> &points)
{
    for (int i = 0; i < points.size() - 1; i++)
    {
        if (collidedWithLandscape(points[i], points[i + 1]))
        {
            handleVehicleCrash();
        }
    }
}

bool Vehicle::collidedWithMeteorite(const Meteorite &meteorite) const
{
    return !isOnPlatform &&
           getPosition().y - getSize().height / 3 < meteorite.getPosition().y + meteorite.getRadius() &&
           getPosition().x + getSize().width / 3 > meteorite.getPosition().x - meteorite.getRadius() &&
           getPosition().y + getSize().height / 3 > meteorite.getPosition().y - meteorite.getRadius() &&
           getPosition().x - getSize().width / 3 < meteorite.getPosition().x + meteorite.getRadius();
}

void Vehicle::updateCollidedWithMeteorite(std::vector<Meteorite> &meteorites)
{
    for (Meteorite &meteorite: meteorites)
    {
        if (collidedWithMeteorite(meteorite))
        {
            handleVehicleCrash();
        }
    }
}

void Vehicle::updateTilt()
{
    if (velocity.x > 0)
    {
        rotation += std::min(velocity.x * TIME_STEP, MAX_TILT_ANGLE - rotation);
    } else if (velocity.x < 0)
    {
        rotation += std::max(velocity.x * TIME_STEP, -MAX_TILT_ANGLE - rotation);
    } else
    {
        if (rotation > 0)
        {
            rotation = std::max(rotation - RETURN_ANGLE_SPEED * TIME_STEP, 0.f);
        } else if (rotation < 0)
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

void Vehicle::handleVehicleCrash()
{
    isCrashed = true;
    setRotation(0);
    setVelocity({0, 0});
    setAcceleration({0, 0});
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

void Vehicle::setRotation(const float newRotation)
{
    rotation = newRotation;
}
