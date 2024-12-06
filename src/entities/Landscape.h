#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <string>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>

#include "../utils/Size.h"

class Landscape {
public:
    Landscape();
    // void init(float x, float y);

    void updateLandscape(float step, float minHeight, float maxHeight);

    void createLandscape(std::vector<sf::ConvexShape> &arrayOfLandscapes);

    void updatePosition(const std::string &direction, const sf::Vector2f &velocity);

    void drawLandscapes(std::vector<sf::ConvexShape> &arrayOfLandscapes, sf::RenderWindow &window);

    void setPosition(sf::Vector2f newPosition);

    std::vector<sf::ConvexShape> landscapes;
    std::vector<sf::Vector2f> points;

    // void moveForward();
    // void updatePosition(const std::string &direction, const sf::Vector2f &velocity);

    // sf::ConvexShape getLandscape();
    sf::Vector2f getPosition() const;
    // Size getSize() const;
    // void setPosition(float x, float y);


private:
    sf::ConvexShape landscape;
    // Size size;
};



#endif //LANDSCAPE_H
