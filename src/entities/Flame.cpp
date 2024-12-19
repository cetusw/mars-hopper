#include "Flame.h"
#include "../utils/utils.cpp"
#include "../utils/constants.h"

Flame::Flame() : rotation(0), frameColumn(0), frameRow(0), currentFrameIndex(0), elapsedTime(0), isAnimating(false)
{
}

void Flame::init(const std::string &filePath, const Size size)
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

    loadSound(engineBuffer, ENGINE_SOUND);
    engineSound.setBuffer(engineBuffer);
}

void Flame::onEngine()
{
    if (engineSound.getStatus() != sf::Sound::Playing)
    {
        engineSound.play();
    }
    if (!isAnimating)
    {
        isAnimating = true;
        currentFrameIndex = 0;
        flameSprite.setTextureRect(currentFrame);
    } else
    {
        currentFrameIndex = 9;
        updateCurrentFrame();
        flameSprite.setTextureRect(currentFrame);
    }
}

void Flame::update(const int startFrame, const int endFrame)
{
    if (!isAnimating)
    {
        engineSound.stop();
        return;
    }

    elapsedTime += TIME_STEP;

    if (elapsedTime >= frameDuration)
    {
        elapsedTime -= frameDuration;

        currentFrameIndex += 1;
        if (currentFrameIndex > endFrame)
        {
            currentFrameIndex = startFrame;
            isAnimating = false;
        }

        updateCurrentFrame();

        flameSprite.setTextureRect(currentFrame);
    }
}

void Flame::updateCurrentFrame()
{
    frameColumn = currentFrameIndex % frameColumns;
    frameRow = currentFrameIndex / frameColumns;

    currentFrame.left = frameColumn * frameWidth;
    currentFrame.top = frameRow * frameHeight;
}

void Flame::updateEnginePosition(const sf::Vector2f offset, const sf::Vector2f &vehiclePosition)
{
    sf::Transform engineTransform;
    engineTransform.rotate(rotation, vehiclePosition);
    const sf::Vector2f enginePosition = engineTransform.transformPoint(vehiclePosition + offset);
    setPosition(enginePosition);
    setRotation(rotation);
}

sf::Vector2f Flame::getPosition() const
{
    return flameSprite.getPosition();
}

void Flame::setPosition(const sf::Vector2f position)
{
    flameSprite.setPosition(position);
}

void Flame::setRotation(const float degrees)
{
    flameSprite.setRotation(degrees);
}

void Flame::draw(sf::RenderWindow &window) const
{
    window.draw(flameSprite);
}
