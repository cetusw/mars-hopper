#include "Landscape.h"
#include "../utils/utils.cpp"
#include "../utils/constants.h"

Landscape::Landscape() : landscape(sf::TriangleStrip)
{
}

void Landscape::updateLandscape(const float step, const float minHeight, const float maxHeight)
{
    while (!points.empty() && points[0].x < -10000)
    {
        points.erase(points.begin());
        points.erase(points.begin());
    }

    while (points.empty() || points.back().x < WINDOW_WIDTH + 10000)
    {
        sf::Vector2f point;
        if (points.empty())
        {
            point.x = -10000;
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
        landscape.setPoint(1, {LANDSCAPE_STEP, points[i + 1].y - points[i].y});
        landscape.setPoint(2, {LANDSCAPE_STEP, 1000});
        landscape.setPoint(3, {0, 1000});
        if (i % 2 == 0)
        {
            landscape.setFillColor(sf::Color(0x67, 0x05, 0x00));
        } else
        {
            landscape.setFillColor(sf::Color(0x88, 0x1D, 0x0B));
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
        } else if (direction == "vertical")
        {
            point = {point.x, point.y - velocity.y * TIME_STEP};
        }
    }
}

void Landscape::drawLandscapes(std::vector<sf::ConvexShape> &arrayOfLandscapes, sf::RenderWindow &window)
{
    for (sf::ConvexShape &landscape: arrayOfLandscapes)
    {
        window.draw(landscape);
    }
}

sf::Vector2f Landscape::getPosition() const
{
    return landscape.getPosition();
}

void Landscape::setPosition(const sf::Vector2f newPosition)
{
    landscape.setPosition(newPosition);
}
