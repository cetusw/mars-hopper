#include "Platform.h"

#include <iostream>

Platform::Platform() : size{400.f, 50.f} {}

void Platform::init(const float x, const float y)
{
    body.setPosition({x, y});
    body.setPointCount(4);
    body.setPoint(0, {0, 0});
    body.setPoint(1, {size.width, 0});
    body.setPoint(2, {size.width, size.height});
    body.setPoint(3, {0, size.height});
    body.setPosition(x, y);
    body.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
}

sf::Vector2f Platform::getPosition() const
{
    return body.getPosition();
}

Size Platform::getSize() const
{
    return size;
}

sf::ConvexShape& Platform::getBody() {
    return body;
}

