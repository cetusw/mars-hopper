#include "Platform.h"

#include "../utils/Constants.h"
#include "../utils/RandomGenerator.h"

Platform::Platform() : size{PLATFORM_SIZE}
{
}

void Platform::init(const float x, const float y)
{
    top.setPosition(x, y);
    top.setPointCount(4);
    top.setPoint(0, {0, 0});
    top.setPoint(1, {size.width, 0});
    top.setPoint(2, {size.width, size.height});
    top.setPoint(3, {0, size.height});
    top.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    bottom.setPosition(x, y);
    bottom.setPointCount(4);
    bottom.setPoint(0, {0, 0});
    bottom.setPoint(1, {size.width, 0});
    bottom.setPoint(2, {size.width + 500.f, size.height + WINDOW_HEIGHT});
    bottom.setPoint(3, {-500.f, size.height + WINDOW_HEIGHT});
    bottom.setFillColor(sf::Color(0xFF, 0x00, 0x00));
}

void Platform::moveForward()
{
    if (getPosition().x + getSize().width < -WINDOW_WIDTH - 500)
    {
        setPosition(
            WINDOW_WIDTH + 500,
            getRandomNumber(200, GROUND_LEVEL)
        );
    }
}

void Platform::updatePosition(const std::string &direction, const sf::Vector2f &velocity)
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

sf::Vector2f Platform::getPosition()
{
    return top.getPosition();
}

Size Platform::getSize() const
{
    return size;
}

sf::ConvexShape &Platform::getTop()
{
    return top;
}

sf::ConvexShape &Platform::getLandscape()
{
    return bottom;
}

void Platform::setPosition(const float x, const float y)
{
    top.setPosition(x, y);
    bottom.setPosition(x, y);
}
