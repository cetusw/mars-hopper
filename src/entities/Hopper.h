#ifndef HOPPER_H
#define HOPPER_H

#include <SFML/Graphics.hpp>
#include "../utils/Size.h"

class Hopper {
public:
    Hopper();
    void init(const std::string &filePath);
    void updatePosition();
    void reduceAccelerationX();
    void reduceAccelerationY();
    void handleInput(sf::Keyboard::Key key);
    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    sf::Vector2f getAcceleration() const;
    Size getSize() const;
    sf::Sprite& getBody();
    void setPosition(sf::Vector2f position);
    void setVelocity(sf::Vector2f newVelocity);
    void setAcceleration(sf::Vector2f newAcceleration);

private:
    sf::Sprite body;
    sf::Texture texture;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f position;
    Size size;
};

#endif //HOPPER_H
