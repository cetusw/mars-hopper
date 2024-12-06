#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <string>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Landscape
{
public:
    Landscape();

    void updateLandscape(float step, float minHeight, float maxHeight);

    void createLandscape(std::vector<sf::ConvexShape> &arrayOfLandscapes);

    void updatePosition(const std::string &direction, const sf::Vector2f &velocity);

    void drawLandscapes(std::vector<sf::ConvexShape> &arrayOfLandscapes, sf::RenderWindow &window);

    void setPosition(sf::Vector2f newPosition);

    std::vector<sf::ConvexShape> landscapes;
    std::vector<sf::Vector2f> points;

    sf::Vector2f getPosition() const;

private:
    sf::ConvexShape landscape;
};

#endif //LANDSCAPE_H
