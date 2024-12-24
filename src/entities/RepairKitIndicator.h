#ifndef REPAIRKITINDICATOR_H
#define REPAIRKITINDICATOR_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../utils/Size.h"


class RepairKitIndicator
{
public:
    RepairKitIndicator();

    void init();

    bool getDrawability() const;

    sf::Sprite getSprite();

    void setDrawability(bool state);

private:
    sf::Sprite repairKitIndicatorSprite;
    sf::Texture repairKitIndicatorTexture;
    Size repairKitIndicatorSize;
    bool isDrawable;
};


#endif //REPAIRKITINDICATOR_H
