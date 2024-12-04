#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../entities/Landscape.h"
#include "../entities/Menu.h"
#include "../entities/Vehicle.h"
#include "../entities/Platform.h"
#include "../utils/GameState.h"

class Game {
public:
    Game();
    void run();
    std::vector<Platform> platforms;
    std::vector<Landscape> landscapes;
    Landscape landscape;
    Vehicle vehicle;

private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::VertexArray landscapePoint;
    GameState gameState;
    sf::SoundBuffer gameBuffer;
    sf::Sound gameSound;
    Menu menu;

    void init();

    void reset();

    void initBackground(const std::string &filePath);
    void handlePlaying();
    void update();
    void draw();
    void pollEvents();
    void updateMapPosition();
    void updatePlatformsPosition(const std::string &direction);
    void updateLandscapesPosition(const std::string &direction);
};



#endif //GAME_H
