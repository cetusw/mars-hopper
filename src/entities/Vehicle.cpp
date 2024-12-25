#include "Vehicle.h"
#include <iostream>
#include "../utils/utils.cpp"
#include "Platform.h"
#include "../game/Game.h"
#include "../utils/constants.h"

Vehicle::Vehicle() : isCrashed(false), isOnPlatform(false), fuel(100), amountOfSafetyFactor(3), velocity{0, 0}, acceleration{0, 0},
                     position{VEHICLE_START_POSITION},
                     rotation(0), size{VEHICLE_SIZE}, isRepairable(false)
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

    leftEngine.init(FLAME_IMAGE, ENGINE_SIZE, {FRAME_WIDTH / 2, FRAME_HEIGHT / 2});
    leftEngine.setRotation(15.0f);
    rightEngine.init(FLAME_IMAGE, ENGINE_SIZE, {FRAME_WIDTH / 2, FRAME_HEIGHT / 2});
    rightEngine.setRotation(-15.0f);

    passedPlatforms.clear();

    loadSound(vehicleBuffer, "../assets/sounds/meteorite-crash.wav");
    vehicleSound.setBuffer(vehicleBuffer);
}

void Vehicle::playVehicleCrashSound()
{
    if (vehicleSound.getStatus() != sf::Sound::Playing)
    {
        vehicleSound.play();
    }
}

void Vehicle::updatePosition()
{
    setPosition(
        {getPosition().x + getVelocity().x * TIME_STEP, getPosition().y + getVelocity().y * TIME_STEP}
    );
    reduceAccelerationX();
    reduceAccelerationY();
    reduceVelocityX();
    reduceVelocityY();
    updateTilt();
    updateEngines();
}

void Vehicle::reduceVelocityX()
{
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
    velocity.x += acceleration.x;
}

void Vehicle::reduceVelocityY()
{
    if (!isOnPlatform)
    {
        velocity.y += FREE_FALL_ACCELERATION - acceleration.y;
    }
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

void Vehicle::reduceFuel(const float engineNumber)
{
    if (fuel > ENGINE_FUEL_CONSUMPTION * engineNumber)
    {
        fuel -= ENGINE_FUEL_CONSUMPTION * engineNumber;
    } else
    {
        fuel = 0;
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
        reduceFuel(2);
        leftEngine.onEngine();
        rightEngine.onEngine();
        increaseVerticalAcceleration();
    }
    if (key == sf::Keyboard::Left)
    {
        reduceFuel(1);
        increaseDiagonalAcceleration("left");
        leftEngine.onEngine();
    }
    if (key == sf::Keyboard::Right)
    {
        reduceFuel(1);
        increaseDiagonalAcceleration("right");
        rightEngine.onEngine();
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
           getPosition().x + getSize().width / 2.0f > platform.getPosition().x - PLATFORM_OFFSET_X &&
           getPosition().x - getSize().width / 2.0f < platform.getPosition().x + PLATFORM_OFFSET_X &&
           getPosition().y - getSize().height / 2.0f < platform.getPosition().y + PLATFORM_OFFSET_Y;
}

bool Vehicle::updateCollidedWithPlatforms(std::vector<Platform> &platforms, AchievementManager &achievementManager)
{
    for (Platform &platform: platforms)
    {
        if (!collidedWithPlatform(platform))
        {
            continue;
        }
        if (std::hypot(velocity.x, velocity.y) > MAX_AllOWED_SPEED)
        {
            if (isVehicleCrashed())
            {
                break;
            }
        }
        increasePlatformNumber(platform.getId(), achievementManager);
        handleRepair(platform);
        handleTouchdown(platform);
        return true;
    }
    return false;
}

void Vehicle::handleTouchdown(const Platform &platform)
{
    fuel = MAX_FUEL_AMOUNT;
    isOnPlatform = true;
    setVelocity({0, 0});
    setPosition({
        getPosition().x,
        platform.getPosition().y - getSize().height / 2.0f + PLATFORM_OFFSET_Y
    });
}

void Vehicle::handleRepair(Platform &platform)
{
    if (platform.getRepairStatus() && isRepairable && amountOfSafetyFactor != MAX_SAFETY_FACTOR_AMOUNT)
    {
        amountOfSafetyFactor = MAX_SAFETY_FACTOR_AMOUNT;
        isRepairable = false;
    }
    if (platform.getRepairKitStatus() && !isRepairable)
    {
        isRepairable = true;
        platform.setRepairKit(false);
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
            setVelocity({getVelocity().x + meteorite.getVelocity().x / 2, getVelocity().y + meteorite.getVelocity().y / 2});
            meteorite.handleMeteoriteOverflow();
            if (isVehicleCrashed())
            {
                break;
            }
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

void Vehicle::updateEngines()
{
    leftEngine.update(ENGINE_FLAME_START_FRAME, ENGINE_FLAME_END_FRAME);
    rightEngine.update(ENGINE_FLAME_START_FRAME, ENGINE_FLAME_END_FRAME);
    leftEngine.rotation = rotation + ENGINE_ANGLE;
    rightEngine.rotation = rotation - ENGINE_ANGLE;
    leftEngine.updateEnginePosition({ENGINE_OFFSET_X, -ENGINE_OFFSET_Y}, getPosition());
    rightEngine.updateEnginePosition({-ENGINE_OFFSET_X, -ENGINE_OFFSET_Y}, getPosition());
}

bool Vehicle::isVehicleCrashed()
{
    amountOfSafetyFactor -= 1;
    if (amountOfSafetyFactor == 0)
    {
        handleVehicleCrash();
        return true;
    }
    return false;
}

void Vehicle::handleVehicleCrash()
{
    isCrashed = true;
    playVehicleCrashSound();
    reset();
    if (loadProgress() < passedPlatforms.size())
    {
        saveProgress(passedPlatforms.size());
    }
}

void Vehicle::increasePlatformNumber(const int currentPlatformId, AchievementManager &achievementManager)
{
    if (std::ranges::find(passedPlatforms, currentPlatformId) == passedPlatforms.end() && !isCrashed)
    {
        passedPlatforms.emplace_back(currentPlatformId);
    } else if (currentPlatformId != passedPlatforms.back() && !isCrashed)
    {
        achievementManager.unlock("Back?");
    }
}

void Vehicle::reset()
{
    fuel = MAX_FUEL_AMOUNT;
    amountOfSafetyFactor = MAX_SAFETY_FACTOR_AMOUNT;
    isOnPlatform = false;
    leftEngine.stopEngineSound();
    rightEngine.stopEngineSound();
    leftEngine.isAnimating = false;
    rightEngine.isAnimating = false;
    isRepairable = false;
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

std::vector<int> Vehicle::getPassedPlatforms()
{
    return passedPlatforms;
}

float Vehicle::getRotation() const
{
    return rotation;
}

bool Vehicle::getRepairability() const
{
    return isRepairable;
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
