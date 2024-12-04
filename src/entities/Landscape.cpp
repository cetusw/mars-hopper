#include "Landscape.h"
#include <cmath>
#include "../utils/constants.h"

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

float Landscape::interpolate(const float a, const float b, const float t) {
    return a + t * (b - a);
}

float Landscape::noise(const float x) {
    const int x0 = static_cast<int>(std::floor(x)); // Левый "узел"
    const int x1 = x0 + 1;                         // Правый "узел"

    const float t = x - x0;                        // Доля между узлами

    const float rand0 = std::sin(x0) * 43758.5453f; // Генерация псевдослучайного значения
    const float rand1 = std::sin(x1) * 43758.5453f;

    return interpolate(rand0 - std::floor(rand0), rand1 - std::floor(rand1), t);
}

std::vector<float> Landscape::generateHeights(const int width, const float scale) {
    std::vector<float> heights(width);
    for (int i = 0; i < width; ++i) {
        heights[i] = noise(i * scale) * MAX_GROUND_HEIGHT; // noise() — функция шума Перлина
    }
    return heights;
}
