#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "../entities/GameBackground.h"
#include "../entities/Hopper.h"
#include "../entities/Platform.h"

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    Hopper hopper;
    std::vector<Platform> platforms;
    GameBackground background;

    void init();
    void update(float deltaTime);
    void draw();
    void pollEvents();
    static bool collidedWithPlatform(const Hopper &hopper, const Platform &platform);
};



#endif //GAME_H
