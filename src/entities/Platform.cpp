#include "Platform.h"
#include "../utils/utils.cpp"
#include "../utils/constants.h"

Platform::Platform() : size{PLATFORM_SIZE}
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
}

void Platform::moveForward(std::vector<sf::Vector2f> &points)
{
    if (getPosition().x + getSize().width < -WINDOW_WIDTH - 500)
    {
        setPosition(
            WINDOW_WIDTH + 500,
            getPlatformPositionY(WINDOW_WIDTH + 500, points)
        );
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

float Platform::getPlatformPositionY(const float x, std::vector<sf::Vector2f> &points)
{
    for (const sf::Vector2f point: points)
    {
        if (x + LANDSCAPE_STEP < point.x && point.x > 0)
        {
            std::cout << point.x << std::endl;
            return point.y - 350;
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

void Platform::setPosition(const float x, const float y)
{
    body.setPosition(x, y);
}
