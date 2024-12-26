#include "Landscape.h"
#include "../utils/utils.cpp"
#include "../utils/constants.h"

Landscape::Landscape() : landscape(sf::TriangleStrip)
{
}

void Landscape::updateLandscape()
{
    bool steepPhase = false;
    int steepPhaseLength = 0;
    clearLandscapePoints();

    if (getRandomNumber(0, 1) > 0.2)
    {
        steepPhase = true;
    }

    while (points.empty() || points.back().x < WINDOW_WIDTH + LANDSCAPE_OVERFLOW_LENGTH)
    {
        sf::Vector2f point;
        calculateLandscapePoints(point, steepPhase, steepPhaseLength);
        checkLandscapePointsHeight(point);
        points.emplace_back(point.x, point.y);
    }

    createLandscape(landscapes);
}

void Landscape::clearLandscapePoints()
{
    while (!points.empty() && points[0].x < -LANDSCAPE_OVERFLOW_LENGTH)
    {
        points.erase(points.begin());
        points.erase(points.begin());
    }
}

void Landscape::calculateLandscapePoints(sf::Vector2f &point, bool &steepPhase, int &steepPhaseLength) const
{
    if (points.empty())
    {
        point.x = -10000;
        point.y = getRandomNumber(LANDSCAPE_MIN_HEIGHT, LANDSCAPE_MAX_HEIGHT);
        return;
    }
    if (steepPhase && steepPhaseLength <= LANDSCAPE_STEEP_PHASE_LENGTH)
    {
        steepPhaseLength++;
        point.x = points.back().x + LANDSCAPE_STEP;
        point.y = points.back().y + getRandomNumber(-LANDSCAPE_STEEP_PHASE_LEVEL_OFFSET, LANDSCAPE_STEEP_PHASE_LEVEL_OFFSET);
    } else
    {
        steepPhase = false;
        steepPhaseLength = 0;
        point.x = points.back().x + LANDSCAPE_STEP;
        point.y = points.back().y + getRandomNumber(-LANDSCAPE_LEVEL_OFFSET, LANDSCAPE_LEVEL_OFFSET);
    }
}

void Landscape::checkLandscapePointsHeight(sf::Vector2f &point)
{
    if (point.y < LANDSCAPE_MIN_HEIGHT)
    {
        point.y = LANDSCAPE_MIN_HEIGHT;
    }
    if (point.y > LANDSCAPE_MAX_HEIGHT)
    {
        point.y = LANDSCAPE_MAX_HEIGHT;
    }
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

sf::Vector2f Landscape::getPosition() const
{
    return landscape.getPosition();
}

void Landscape::setPosition(const sf::Vector2f newPosition)
{
    landscape.setPosition(newPosition);
}
