#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>
#include "../utils/Size.h"

class Platform {
public:
    Platform();
    void init(float x, float y);
    sf::Vector2f getPosition() const;
    Size getSize() const;
    sf::ConvexShape& getTop();
    sf::ConvexShape& getLandscape();

private:
    sf::ConvexShape top;
    sf::ConvexShape landscape;
    Size size;
};



#endif //PLATFORM_H