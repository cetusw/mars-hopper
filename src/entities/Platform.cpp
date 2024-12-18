#include "Platform.h"
#include "../utils/utils.cpp"
#include "../utils/constants.h"

int Platform::lastId = 0;

Platform::Platform() : id(0), size{PLATFORM_SIZE}
{
}

void Platform::init(const float x, const float y, const std::string &filePath)
{
    loadTexture(texture, filePath);
    body.setTexture(texture);
    body.setScale(
        size.width / static_cast<float>(texture.getSize().x),
        size.height / static_cast<float>(texture.getSize().y)
    );
    body.setPosition(x, y);

    id = ++lastId;
}

void Platform::moveForward(std::vector<sf::Vector2f> &points)
{
    if (getPosition().x + getSize().width < -WINDOW_WIDTH)
    {
        setPosition(
            WINDOW_WIDTH + WINDOW_EXPAND,
            getPlatformPositionY(WINDOW_WIDTH, points)
        );
        setId();
    }
}

void Platform::updatePosition(const std::string &direction, const sf::Vector2f &velocity, std::vector<sf::Vector2f> &points)
{
    if (direction == "horizontal")
    {
        setPosition(getPosition().x - velocity.x * TIME_STEP, getPosition().y);
    } else if (direction == "vertical")
    {
        setPosition(getPosition().x, getPosition().y - velocity.y * TIME_STEP);
    }
    moveForward(points);
}

void Platform::updatePlatformsPosition(const std::string &direction, std::vector<sf::Vector2f> &points, std::vector<Platform> &platforms, const sf::Vector2f velocity)
{
    for (Platform &platform: platforms)
    {
        platform.updatePosition(direction, velocity, points);
    }
}

float Platform::getPlatformPositionY(const float x, std::vector<sf::Vector2f> &points)
{
    for (const sf::Vector2f point: points)
    {
        if (x + LANDSCAPE_STEP < point.x && point.x > 0)
        {
            return point.y - PLATFORM_OFFSET_Y_FOR_INSERT;
        }
    }
}

sf::Vector2f Platform::getPosition() const
{
    return body.getPosition();
}

Size Platform::getSize() const
{
    return size;
}

sf::Sprite Platform::getBody()
{
    return body;
}

int Platform::getId() const
{
    return id;
}

void Platform::setPosition(const float x, const float y)
{
    body.setPosition(x, y);
}

void Platform::setId()
{
    id = ++lastId;
}
