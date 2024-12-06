#include "Landscape.h"

#include <iostream>

#include "../utils/randomGenerator.cpp"
#include "../utils/constants.h"


Landscape::Landscape() : landscape(sf::TriangleStrip)
{

}

// void Landscape::init(const float x, const float y)
// {
//     landscape.setPosition(x, y);
//     landscape.setPointCount(4);
//     landscape.setPoint(0, {0, 0});
//     landscape.setPoint(1, {size.width, 0});
//     landscape.setPoint(2, {size.width + 500.f, size.height});
//     landscape.setPoint(3, {-500.f, size.height});
//     landscape.setFillColor(sf::Color(0xFF, 0x00, 0x00));
// }

void Landscape::updateLandscape(const float step, const float minHeight, const float maxHeight)
{
    while (!points.empty() && points[0].x < -1000)
    {
        points.erase(points.begin());
        points.erase(points.begin());
    }

    while (points.empty() || points.back().x < WINDOW_WIDTH)
    {
        sf::Vector2f point;
        if (points.empty())
        {
            point.x = 0;
            point.y = getRandomNumber(minHeight, maxHeight);
        } else
        {
            point.x = points.back().x + step;
            point.y = points.back().y + getRandomNumber(-20, 20);
        }

        if (point.y < minHeight)
        {
            point.y = minHeight;
        }
        if (point.y > maxHeight)
        {
            point.y = maxHeight;
        }

        points.emplace_back(point.x, point.y);
    }

    createLandscape(landscapes);
}

void Landscape::createLandscape(std::vector<sf::ConvexShape> &arrayOfLandscapes)
{
    arrayOfLandscapes.clear();
    for (int i = 0; i < points.size(); ++i)
    {
        landscape.setPosition(points[i].x, points[i].y);
        landscape.setPointCount(4);
        landscape.setPoint(0, {0, 0});
        landscape.setPoint(1, {LANDSCAPE_STEP, points[i+1].y - points[i].y});
        landscape.setPoint(2, {LANDSCAPE_STEP, 1000});
        landscape.setPoint(3, {0, 1000});
        if (i % 2 == 0)
        {
            landscape.setFillColor(sf::Color(0xFF, 0x00, 0x00));
        }
        else
        {
            landscape.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
        }

        arrayOfLandscapes.emplace_back(landscape);
    }
}

void Landscape::updatePosition(const std::string &direction, const sf::Vector2f &velocity)
{

    for (sf::Vector2f &point: points)
    {
        if (direction == "horizontal")
        {
            point = {point.x - velocity.x * TIME_STEP, point.y};
        }
        else if (direction == "vertical")
        {
            point = {point.x, point.y - velocity.y * TIME_STEP};
        }
    }
}

void Landscape::drawLandscapes(std::vector<sf::ConvexShape> &arrayOfLandscapes, sf::RenderWindow &window)
{
    for (sf::ConvexShape &landscape : arrayOfLandscapes)
    {
        window.draw(landscape);
    }
}

// void Landscape::moveForward()
// {
//     if (getPosition().x + getSize().width < -WINDOW_WIDTH)
//     {
//         setPosition(
//             WINDOW_WIDTH,
//             GROUND_LEVEL
//         );
//     }
// }
//
// void Landscape::updatePosition(const std::string &direction, const sf::Vector2f &velocity)
// {
//     if (direction == "horizontal")
//     {
//         setPosition(getPosition().x - velocity.x * TIME_STEP, getPosition().y);
//     } else if (direction == "vertical")
//     {
//         setPosition(getPosition().x, getPosition().y - velocity.y * TIME_STEP);
//     }
//     moveForward();
// }

// sf::ConvexShape Landscape::getLandscape()
// {
//     return landscape;
// }

sf::Vector2f Landscape::getPosition() const
{
    return landscape.getPosition();
}

// Size Landscape::getSize() const
// {
//     return size;
// }


void Landscape::setPosition(const sf::Vector2f newPosition)
{
    landscape.setPosition(newPosition);
}
