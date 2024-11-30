#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>
#include "../utils/Size.h"

class Platform {
public:
    Platform();
    void init(float x, float y);
    void moveForward();
    void updatePosition(const std::string &direction, const sf::Vector2f &velocity);

    sf::Vector2f getPosition() const;
    Size getSize() const;
    sf::ConvexShape& getTop();
    sf::ConvexShape& getLandscape();
    void setPosition(float x, float y);

private:
    sf::ConvexShape top;
    sf::ConvexShape bottom;
    Size size;
};

#endif //PLATFORM_H
