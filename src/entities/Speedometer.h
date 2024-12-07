#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>


class Speedometer {
public:
    Speedometer();

    void init();

    void updateSpeedometer(sf::Vector2f speed, sf::Vector2f position);

    void handleSpeeding(float speed);

    sf::Text speedText;

private:
    sf::Font font;
};



#endif //SPEEDOMETER_H
