#ifndef THRUSTERANIMATION_H
#define THRUSTERANIMATION_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio.hpp>

#include "../utils/Size.h"

class Engine {
public:
    Engine();
    void init(const std::string &filePath);

    void start();

    void stop();

    void update();
    void updateCurrentFrame();
    void updateThrusterPosition(sf::Vector2f offset, const sf::Vector2f &vehiclePosition);
    void draw(sf::RenderWindow& window) const;
    void thrust();
    Size getSize() const;
    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f position);
    void setRotation(float degrees);

    float rotation;

private:
    sf::Sprite flameSprite;
    sf::Texture flameTexture;
    sf::IntRect currentFrame;
    Size size;
    int frameWidth = 128;
    int frameHeight = 126;
    int frameColumns = 6;
    int frameRows = 5;
    int frameCount = frameRows * frameColumns;
    int frameColumn;
    int frameRow;
    int currentFrameIndex;
    float frameDuration = 0.03f;
    float elapsedTime;
    bool isAnimating;
    std::string thrusterState;
    sf::SoundBuffer thrusterBuffer;
    sf::Sound thrusterSound;
    bool isRunning = false;
};



#endif //THRUSTERANIMATION_H
