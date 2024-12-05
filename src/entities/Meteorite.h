#ifndef METEORITE_H
#define METEORITE_H
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

#include "Landscape.h"
#include "Platform.h"


class Meteorite {
public:
    Meteorite();

    void init();

    void handleMeteoriteOverflow();

    void updatePosition(const std::string &direction, const sf::Vector2f &velocity);

    bool collidedWithPlatform(const Platform &platform) const;

    void updateCollidedWithPlatforms(std::vector<Platform> &platforms);

    bool collidedWithLandscape(const Landscape &landscape) const;

    void updateCollidedWithLandscape(std::vector<Landscape> &landscapes);

    sf::CircleShape getBody();

    sf::Vector2f getVelocity() const;

    float getRadius() const;

    sf::Vector2f getPosition() const;

    void setPosition(sf::Vector2f position);

    void setVelocity(sf::Vector2f newVelocity);


    bool isFalling;

private:
    sf::CircleShape body;
    float radius;
    sf::Vector2f position;
    sf::Vector2f velocity;

};



#endif //METEORITE_H
