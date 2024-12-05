#include "Meteorite.h"
#include "../utils/constants.h"
#include "../utils/randomGenerator.cpp"

Meteorite::Meteorite(): isFalling(false), radius(METEORITE_RADIUS), velocity({0, 0})
{
}

void Meteorite::init()
{
    body.setRadius(radius);
    body.setOrigin(body.getRadius(), body.getRadius());
    body.setPosition(getRandomNumber(WINDOW_WIDTH + 1000, WINDOW_WIDTH + 2000), -800);
    body.setFillColor(sf::Color::Black);
    isFalling = false;
}

void Meteorite::handleMeteoriteOverflow()
{
    setPosition({getRandomNumber(WINDOW_WIDTH + 1000, WINDOW_WIDTH + 2000), -800});
    setVelocity({0, 0});
    isFalling = false;
}

void Meteorite::updatePosition(const std::string &direction, const sf::Vector2f &velocity)
{
    if (direction == "horizontal")
    {
        setPosition({getPosition().x - velocity.x * TIME_STEP, getPosition().y});
    }
    else if (direction == "vertical")
    {
        setPosition({getPosition().x, getPosition().y - velocity.y * TIME_STEP});
    }
}

bool Meteorite::collidedWithPlatform(const Platform &platform) const
{
    const sf::Vector2f leftLineStart = {platform.getPosition().x, platform.getPosition().y};
    const sf::Vector2f leftLineEnd = {platform.getPosition().x - 500, platform.getPosition().y + WINDOW_HEIGHT};
    const sf::Vector2f rightLineStart = {platform.getPosition().x + platform.getSize().width, platform.getPosition().y};
    const sf::Vector2f rightLineEnd = {platform.getPosition().x + platform.getSize().width + 500, platform.getPosition().y + WINDOW_HEIGHT};

    const float leftK = (leftLineEnd.y - leftLineStart.y) / (leftLineEnd.x - leftLineStart.x);
    const float leftB = leftLineStart.y - leftK * leftLineStart.x;

    const float rightK = (rightLineEnd.y - rightLineStart.y) / (rightLineEnd.x - rightLineStart.x);
    const float rightB = rightLineStart.y - rightK * rightLineStart.x;

    return getPosition().y + getRadius() > leftK * (getPosition().x + getRadius()) + leftB &&
           getPosition().y + getRadius() > rightK * (getPosition().x - getRadius()) + rightB &&
           getPosition().y + getRadius() > platform.getPosition().y;
}

void Meteorite::updateCollidedWithPlatforms(std::vector<Platform> &platforms)
{
    for (Platform &platform: platforms)
    {
        if (collidedWithPlatform(platform))
        {
            handleMeteoriteOverflow();
        }
    }
}

bool Meteorite::collidedWithLandscape(const Landscape &landscape) const
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

    return getPosition().y + getRadius() > leftK * (getPosition().x + getRadius()) + leftB &&
           getPosition().y + getRadius() > rightK * (getPosition().x - getRadius()) + rightB &&
           getPosition().y + getRadius() > landscape.getPosition().y;
}

void Meteorite::updateCollidedWithLandscape(std::vector<Landscape> &landscapes)
{
    for (Landscape &landscape: landscapes)
    {
        if (collidedWithLandscape(landscape))
        {
            handleMeteoriteOverflow();
        }
    }
}

sf::CircleShape Meteorite::getBody()
{
    return body;
}

sf::Vector2f Meteorite::getVelocity() const
{
    return velocity;
}

float Meteorite::getRadius() const
{
    return radius;
}

sf::Vector2f Meteorite::getPosition() const
{
    return body.getPosition();
}

void Meteorite::setPosition(const sf::Vector2f position)
{
    body.setPosition(position);
}

void Meteorite::setVelocity(const sf::Vector2f newVelocity)
{
    velocity = newVelocity;
}
