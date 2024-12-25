#ifndef FLAME_H
#define FLAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio.hpp>

#include "../utils/Size.h"
#include "../utils/constants.h"

class Flame
{
public:
    Flame();

    void init(const std::string &filePath, Size size, sf::Vector2f origin);

    void update(int startFrame, int endFrame);

    void updateCurrentFrame();

    void updateEnginePosition(sf::Vector2f offset, const sf::Vector2f &vehiclePosition);

    void draw(sf::RenderWindow &window) const;

    void stopEngineSound();

    void onEngine();

    sf::Vector2f getPosition() const;

    sf::Sprite getBody();

    void setPosition(sf::Vector2f position);

    void setRotation(float degrees);

    float rotation;
    bool isAnimating;

private:
    sf::Sprite flameSprite;
    sf::Texture flameTexture;
    sf::IntRect currentFrame;
    int frameWidth = FRAME_WIDTH;
    int frameHeight = FRAME_HEIGHT;
    int frameColumns = 6;
    int frameRows = 5;
    int frameCount = frameRows * frameColumns;
    int frameColumn;
    int frameRow;
    int currentFrameIndex;
    float frameDuration = 0.03f;
    float elapsedTime;
    std::string engineState;
    sf::SoundBuffer engineBuffer;
    sf::Sound engineSound;
    bool isRunning = false;
};


#endif //FLAME_H
