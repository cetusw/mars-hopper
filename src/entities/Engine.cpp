#include "Engine.h"

#include "../utils/constants.h"

extern void loadTexture(sf::Texture &texture, const std::string &filePath);
extern void loadSound(sf::SoundBuffer &buffer, const std::string &filePath);

Engine::Engine() : rotation(0), size{500, 500}, frameColumn(0), frameRow(0), currentFrameIndex(0), elapsedTime(0), isAnimating(false)
{
}

void Engine::init(const std::string &filePath)
{
    loadTexture(flameTexture, filePath);
    flameSprite.setTexture(flameTexture);
    flameSprite.setScale(
        size.width / static_cast<float>(flameTexture.getSize().x),
        size.height / static_cast<float>(flameTexture.getSize().y)
    );
    currentFrame = sf::IntRect(0, 0, frameWidth, frameHeight);
    flameSprite.setTextureRect(currentFrame);

    flameSprite.setOrigin(
        static_cast<float>(frameWidth) / 2.f,
        static_cast<float>(frameHeight) / 2.f
    );

    loadSound(thrusterBuffer, "../assets/sounds/engine.wav");
    thrusterSound.setBuffer(thrusterBuffer);
}

void Engine::thrust()
{
    if (thrusterSound.getStatus() != sf::Sound::Playing)
    {
        thrusterSound.play();
    }
    if (!isAnimating)
    {
        isAnimating = true;
        currentFrameIndex = 0;
        flameSprite.setTextureRect(currentFrame);
    }
    else
    {
        currentFrameIndex = 9;
        updateCurrentFrame();
        flameSprite.setTextureRect(currentFrame);
    }
}

void Engine::update()
{
    if (!isAnimating)
    {
        thrusterSound.stop();
        return;
    }

    elapsedTime += TIME_STEP;

    if (elapsedTime >= frameDuration)
    {
        elapsedTime -= frameDuration;

        currentFrameIndex += 1;
        if (currentFrameIndex > frameCount)
        {
            currentFrameIndex = 0;
            isAnimating = false;
        }

        updateCurrentFrame();

        flameSprite.setTextureRect(currentFrame);
    }
}

void Engine::updateCurrentFrame()
{
    frameColumn = currentFrameIndex % frameColumns;
    frameRow = currentFrameIndex / frameColumns;

    currentFrame.left = frameColumn * frameWidth;
    currentFrame.top = frameRow * frameHeight;
}

void Engine::updateThrusterPosition(const sf::Vector2f offset, const sf::Vector2f &vehiclePosition)
{
    sf::Transform thrusterTransform;
    thrusterTransform.rotate(rotation, vehiclePosition);
    const sf::Vector2f thrusterPosition = thrusterTransform.transformPoint(vehiclePosition + offset);
    setPosition(thrusterPosition);
    setRotation(rotation);
}

Size Engine::getSize() const
{
    return size;
}

sf::Vector2f Engine::getPosition() const
{
    return flameSprite.getPosition();
}

void Engine::setPosition(const sf::Vector2f position)
{
    flameSprite.setPosition(position);
}

void Engine::setRotation(const float degrees)
{
    flameSprite.setRotation(degrees);
}

void Engine::draw(sf::RenderWindow &window) const
{
    window.draw(flameSprite);
}
