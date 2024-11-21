#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "../entities/GameBackground.h"
#include "../entities/Landscape.h"
#include "../entities/Vehicle.h"
#include "../entities/Platform.h"

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    Vehicle vehicle;
    std::vector<Platform> platforms;
    GameBackground background;
    std::vector<Landscape> landscapes;

    void init();
    void update();
    void draw();
    void pollEvents();
    static bool collidedWithPlatform(const Vehicle &vehicle, const Platform &platform);
    static bool collidedWithPlatformBottom(const Vehicle &vehicle, const Platform &platform);
    static bool collidedWithLandscape(const Vehicle &vehicle, const Landscape &landscape);
    void updateMapPosition();
    void updateCollidedWithPlatforms();
    void updateCollidedWithLandscape();
    static void movePlatformForward(Platform &platform);
    static void moveLandscapeForward(Landscape &landscape);
    void updatePlatformsPosition(std::string direction);
    void updateLandscapesPosition(std::string direction);
};



#endif //GAME_H
