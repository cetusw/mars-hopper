#ifndef SAFETYFACTOR_H
#define SAFETYFACTOR_H
#include <SFML/Graphics/RectangleShape.hpp>

#include "Vehicle.h"


class SafetyFactor {
public:
    SafetyFactor();

    void init();

    void update(const Vehicle &vehicle);

    void updateSafetyFactorPosition(sf::Vector2f offset, float rotation, const sf::Vector2f &vehiclePosition);

    sf::RectangleShape getBody();

private:
    sf::RectangleShape safetyFactor;
};



#endif //SAFETYFACTOR_H
