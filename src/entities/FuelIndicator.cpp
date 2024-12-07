#include "FuelIndicator.h"
#include <iomanip>

#include "../utils/utils.cpp"
#include "../utils/constants.h"

FuelIndicator::FuelIndicator()
= default;

void FuelIndicator::init()
{
    loadFont(font, BOLD_FONT);
    fuelText.setFont(font);
    fuelText.setCharacterSize(30);
    fuelText.setFillColor(sf::Color::Black);
}

void FuelIndicator::updateFuelIndicator(const float fuel, const sf::Vector2f position)
{
    fuelText.setPosition(position.x - VEHICLE_SIZE.width / 2 - fuelText.getLocalBounds().width, position.y - VEHICLE_SIZE.height / 2);
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(1) << fuel;
    handleFuelEnding(fuel);
    fuelText.setString(stream.str());
}

void FuelIndicator::handleFuelEnding(const float speed)
{
    if (speed <= 30.0f)
    {
        fuelText.setFillColor(sf::Color::Red);
    }
    else
    {
        fuelText.setFillColor(sf::Color::Black);
    }
}