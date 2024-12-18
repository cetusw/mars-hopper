#ifndef MINIMAP_H
#define MINIMAP_H
#include <SFML/Graphics/View.hpp>

#include "Landscape.h"
#include "Vehicle.h"


class MiniMap {
public:
    MiniMap();
    void initMiniMap();

    void updateMiniMap(const Vehicle &vehicle);

    void drawMiniMap(sf::RenderWindow &window, Vehicle &vehicle, std::vector<Platform> &platforms, Landscape &landscape, std::vector<Meteorite> meteorites);

    static void drawMinimapBorder(sf::RenderWindow &window);

private:
    sf::View minimapView;

};



#endif //MINIMAP_H
