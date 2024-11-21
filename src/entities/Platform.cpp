#include "Platform.h"

#include "../utils/Constants.h"

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

sf::Vector2f Platform::getPosition() const
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
