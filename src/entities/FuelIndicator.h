#ifndef FUELINDICATOR_H
#define FUELINDICATOR_H
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>


class FuelIndicator {
public:
    FuelIndicator();

    void init();

    void updateFuelIndicator(float fuel, sf::Vector2f position);

    void handleFuelEnding(float fuelAmount);

    sf::Text fuelText;

private:
    sf::Font font;
};



#endif //FUELINDICATOR_H
