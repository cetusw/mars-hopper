#include "Speedometer.h"

#include <iomanip>

#include "../utils/utils.cpp"
#include "../utils/constants.h"

Speedometer::Speedometer()
= default;

void Speedometer::init()
{
    loadFont(font, BOLD_FONT);
    speedText.setFont(font);
    speedText.setCharacterSize(30);
    speedText.setFillColor(sf::Color::Black);
}

void Speedometer::updateSpeedometer(const sf::Vector2f speed, const sf::Vector2f position)
{
    speedText.setPosition(position.x + VEHICLE_SIZE.width / 2, position.y - VEHICLE_SIZE.height / 2);
    const float currentSpeed = std::hypot(speed.x, speed.y);
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(1) << currentSpeed;
    handleSpeeding(currentSpeed);
    speedText.setString(stream.str());
}

void Speedometer::handleSpeeding(const float speed)
{
    if (speed > 300)
    {
        speedText.setFillColor(sf::Color::Red);
    }
    else
    {
        speedText.setFillColor(sf::Color::Black);
    }
}
