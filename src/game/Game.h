#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "../entities/GameBackground.h"
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

    void init();
    void update(float deltaTime);
    void draw();
    void pollEvents();
    static bool collidedWithPlatform(const Vehicle &vehicle, const Platform &platform);
};



#endif //GAME_H
