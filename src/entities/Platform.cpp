#include "Platform.h"

#include <iostream>
#include "../utils/Constants.h"

Platform::Platform() : size{PLATFORM_SIZE} {}

void Platform::init(const float x, const float y)
{
    top.setPosition(x, y);
    top.setPointCount(4);
    top.setPoint(0, {0, 0});
    top.setPoint(1, {size.width, 0});
    top.setPoint(2, {size.width, size.height});
    top.setPoint(3, {0, size.height});
    top.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    landscape.setPosition(x, y);
    landscape.setPointCount(4);
    landscape.setPoint(0, {0, size.height / 2});
    landscape.setPoint(1, {size.width, size.height / 2});
    landscape.setPoint(2, {size.width + 50.f, size.height + 100.f});
    landscape.setPoint(3, {-50.f, size.height + 100.f});
    landscape.setFillColor(sf::Color(0xFF, 0x00, 0x00));
}

sf::Vector2f Platform::getPosition() const
{
    return top.getPosition();
}

Size Platform::getSize() const
{
    return size;
}

sf::ConvexShape& Platform::getTop() {
    return top;
}

sf::ConvexShape& Platform::getLandscape()
{
    return landscape;
}

