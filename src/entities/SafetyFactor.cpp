#include "SafetyFactor.h"

#include "Vehicle.h"
#include "../utils/constants.h"

SafetyFactor::SafetyFactor()
= default;

void SafetyFactor::init()
{
    safetyFactor.setSize(SAFETY_FACTOR_SIZE);
    safetyFactor.setFillColor(sf::Color::Green);
    safetyFactor.setOrigin(safetyFactor.getSize().x / 2, safetyFactor.getSize().y / 2);
}

void SafetyFactor::update(const Vehicle &vehicle)
{
    updateSafetyFactorPosition({0, SAFETY_FACTOR_OFFSET_Y}, vehicle.getRotation(), vehicle.getPosition());
    switch (vehicle.amountOfSafetyFactor)
    {
        case 3:
            safetyFactor.setFillColor(sf::Color::Green);
            break;
        case 2:
            safetyFactor.setFillColor(sf::Color::Yellow);
            break;
        case 1:
            safetyFactor.setFillColor(sf::Color::Red);
            break;
        default:
            safetyFactor.setFillColor(sf::Color::Green);
    }
}

void SafetyFactor::updateSafetyFactorPosition(const sf::Vector2f offset, const float rotation, const sf::Vector2f &vehiclePosition)
{
    sf::Transform engineTransform;
    engineTransform.rotate(rotation, vehiclePosition);
    const sf::Vector2f enginePosition = engineTransform.transformPoint(vehiclePosition + offset);
    safetyFactor.setPosition(enginePosition);
    safetyFactor.setRotation(rotation);
}

sf::RectangleShape SafetyFactor::getBody()
{
    return safetyFactor;
}
