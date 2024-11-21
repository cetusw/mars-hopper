#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <SFML/Graphics/ConvexShape.hpp>

#include "../utils/Size.h"

class Landscape {
public:
    Landscape();
    void init(float x, float y);
    sf::ConvexShape getLandscape();
    sf::Vector2f getPosition() const;
    Size getSize() const;
    void setPosition(float x, float y);

private:
    sf::ConvexShape landscape;
    Size size;
};



#endif //LANDSCAPE_H
