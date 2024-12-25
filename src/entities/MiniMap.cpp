#include "MiniMap.h"

#include "Landscape.h"
#include "Vehicle.h"
#include "../utils/constants.h"

MiniMap::MiniMap()
= default;

void MiniMap::init()
{
    minimapView.setSize(WINDOW_WIDTH * 1.5f, WINDOW_HEIGHT);
    minimapView.setViewport(sf::FloatRect(0.0f, 0.0f, MINIMAP_SCALE * 1.5f, MINIMAP_SCALE));
}

void MiniMap::updateMiniMap(const Vehicle &vehicle)
{
    minimapView.setCenter(vehicle.getPosition());
}

void MiniMap::drawMiniMap(sf::RenderWindow &window, Vehicle &vehicle, std::vector<Platform> &platforms, Landscape &landscape, std::vector<Meteorite> meteorites) const
{
    const sf::View defaultView = window.getView();
    drawMinimapBorder(window);

    window.setView(minimapView);

    for (Platform &currentPlatform : platforms)
    {
        window.draw(currentPlatform.getBody());
    }
    for (Meteorite &currentMeteorite: meteorites)
    {
        if (!currentMeteorite.isFalling)
        {
            continue;
        }
        window.draw(currentMeteorite.getBody());
        currentMeteorite.flame.draw(window);
    }
    for (sf::ConvexShape &currentLandscape : landscape.landscapes)
    {
        window.draw(currentLandscape);
    }
    window.draw(vehicle.getBody());

    window.setView(defaultView);
}

void MiniMap::drawMinimapBorder(sf::RenderWindow &window)
{
    sf::RectangleShape border;
    border.setSize({WINDOW_WIDTH * MINIMAP_SCALE * 1.5f, WINDOW_HEIGHT * MINIMAP_SCALE});
    border.setPosition(0, 0);
    border.setOutlineColor(sf::Color::Black);
    border.setOutlineThickness(5);
    border.setFillColor(sf::Color(0xfd, 0xd8, 0xa7));
    window.draw(border);
}
