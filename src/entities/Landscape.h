#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <string>
#include <SFML/Graphics/ConvexShape.hpp>

class Landscape
{
public:
    Landscape();

    void updateLandscape();

    void clearLandscapePoints();

    void calculateLandscapePoints(sf::Vector2f &point, bool &steepPhase, int &steepPhaseLength) const;

    static void checkLandscapePointsHeight(sf::Vector2f &point);

    void createLandscape(std::vector<sf::ConvexShape> &arrayOfLandscapes);

    void updatePosition(const std::string &direction, const sf::Vector2f &velocity);

    void setPosition(sf::Vector2f newPosition);

    std::vector<sf::ConvexShape> landscapes;
    std::vector<sf::Vector2f> points;

    sf::Vector2f getPosition() const;

private:
    sf::ConvexShape landscape;
};

#endif //LANDSCAPE_H
