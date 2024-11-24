#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "../entities/Landscape.h"
#include "../entities/Vehicle.h"
#include "../entities/Platform.h"

class Game {
public:
    Game();
    void run();
    std::vector<Platform> platforms;
    std::vector<Landscape> landscapes;
    Vehicle vehicle;

private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    void init();
    void initBackground(const std::string &filePath);
    void update();
    void draw();
    void pollEvents();
    void updateMapPosition();
    void updatePlatformsPosition(const std::string &direction);
    void updateLandscapesPosition(const std::string &direction);
};



#endif //GAME_H
