#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <string>
#include <SFML/Graphics/ConvexShape.hpp>

#include "../utils/Size.h"

class Landscape {
public:
    Landscape();
    void init(float x, float y);

    void moveForward();
    void updatePosition(const std::string &direction, const sf::Vector2f &velocity);

    sf::ConvexShape getLandscape();
    sf::Vector2f getPosition() const;
    Size getSize() const;
    void setPosition(float x, float y);

private:
    sf::ConvexShape landscape;
    Size size;
};



#endif //LANDSCAPE_H
