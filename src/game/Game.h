#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "../entities/Landscape.h"
#include "../entities/Meteorite.h"
#include "../entities/Screen.h"
#include "../entities/Vehicle.h"
#include "../entities/Platform.h"
#include "../utils/GameState.h"

class Game
{
public:
    Game();

    void run();

    std::vector<Platform> platforms;
    Landscape landscape;
    std::vector<Meteorite> meteorites;
    Vehicle vehicle;
    std::vector<sf::Vector2f> points;

private:
    void init();

    void reset();

    void initBackground(const std::string &filePath);

    void handlePlaying();

    void update();

    void draw();

    void pollEvents();

    void updateMapPosition();

    void addMeteorite();

    void updateMeteoritePosition();

    void updatePlatformsPosition(const std::string &direction, std::vector<sf::Vector2f> &points);

    void updateMeteoritesPosition(const std::string &direction);

    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    GameState gameState;
    sf::SoundBuffer gameBuffer;
    sf::Sound gameSound;
    Screen menu;
    float timeSinceLastMeteorite;
};


#endif //GAME_H
