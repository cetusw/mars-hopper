#include "Landscape.h"

#include "../utils/Constants.h"

Landscape::Landscape() : size{WINDOW_WIDTH, WINDOW_HEIGHT}
{
}

void Landscape::init(const float x, const float y)
{
    landscape.setPosition(x, y);
    landscape.setPointCount(4);
    landscape.setPoint(0, {0, 0});
    landscape.setPoint(1, {size.width, 0});
    landscape.setPoint(2, {size.width + 500.f, size.height});
    landscape.setPoint(3, {-500.f, size.height});
    landscape.setFillColor(sf::Color(0xFF, 0x00, 0x00));
}

void Landscape::moveForward()
{
    if (getPosition().x + getSize().width < -WINDOW_WIDTH)
    {
        setPosition(
            WINDOW_WIDTH,
            GROUND_LEVEL
        );
    }
}

void Landscape::updatePosition(const std::string &direction, const sf::Vector2f &velocity)
{
    if (direction == "horizontal")
    {
        setPosition(getPosition().x - velocity.x * TIME_STEP, getPosition().y);
    }
    else if (direction == "vertical")
    {
        setPosition(getPosition().x, getPosition().y - velocity.y * TIME_STEP);
    }
    moveForward();
}

sf::ConvexShape Landscape::getLandscape()
{
    return landscape;
}

sf::Vector2f Landscape::getPosition() const
{
    return landscape.getPosition();
}

Size Landscape::getSize() const
{
    return size;
}


void Landscape::setPosition(const float x, const float y)
{
    landscape.setPosition(x, y);
}
