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
    sf::ConvexShape& getBody();

private:
    sf::ConvexShape body;
    Size size;
};



#endif //PLATFORM_H
