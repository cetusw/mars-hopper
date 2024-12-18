#include "Meteorite.h"
#include "../utils/constants.h"
#include "../utils/utils.cpp"

Meteorite::Meteorite(): isFalling(false), radius(METEORITE_RADIUS), velocity({0, 0})
{
}

void Meteorite::init()
{
    body.setRadius(radius);
    body.setOrigin(body.getRadius(), body.getRadius());
    body.setPosition(getRandomNumber(WINDOW_WIDTH + 1000, WINDOW_WIDTH + 2000), -800);
    body.setFillColor(sf::Color::Black);
    isFalling = false;
}

void Meteorite::addMeteorite(std::vector<Meteorite> &meteorites, float &timeSinceLastMeteorite)
{
    timeSinceLastMeteorite += TIME_STEP;

    if (timeSinceLastMeteorite < getRandomNumber(5, 10))
    {
        return;
    }

    for (Meteorite &meteorite: meteorites)
    {
        timeSinceLastMeteorite = 0.0f;
        if (!meteorite.isFalling)
        {
            meteorite.setPosition({getRandomNumber(WINDOW_WIDTH + 1000, WINDOW_WIDTH + 2000), -800});
            meteorite.setVelocity(METEORITE_VELOCITY);
            meteorite.isFalling = true;
            break;
        }
    }
}

void Meteorite::handleMeteoriteOverflow()
{
    setPosition({getRandomNumber(WINDOW_WIDTH + 1000, WINDOW_WIDTH + 2000), -800});
    setVelocity({0, 0});
    isFalling = false;
}

void Meteorite::updatePosition(const std::string &direction, const sf::Vector2f &velocity)
{
    if (direction == "horizontal")
    {
        setPosition({getPosition().x - velocity.x * TIME_STEP, getPosition().y});
    } else if (direction == "vertical")
    {
        setPosition({getPosition().x, getPosition().y - velocity.y * TIME_STEP});
    }
}

void Meteorite::updateMeteoritePosition(std::vector<Meteorite> &meteorites)
{
    for (Meteorite &meteorite: meteorites)
    {
        if (meteorite.isFalling)
        {
            meteorite.setPosition({
                meteorite.getPosition().x + meteorite.getVelocity().x * TIME_STEP,
                meteorite.getPosition().y + meteorite.getVelocity().y * TIME_STEP
            });
        }
    }
}

void Meteorite::updateMeteoritesPositionRelativeToVehicle(const std::string &direction, std::vector<Meteorite> &meteorites, const sf::Vector2f velocity)
{
    for (Meteorite &meteorite: meteorites)
    {
        meteorite.updatePosition(direction, velocity);
    }
}

bool Meteorite::collidedWithPlatform(const Platform &platform) const
{
    return getPosition().y + getRadius() > platform.getPosition().y + PLATFORM_OFFSET_Y &&
           getPosition().x + getRadius() > platform.getPosition().x + PLATFORM_OFFSET_X &&
           getPosition().x - getRadius() < platform.getPosition().x + platform.getSize().width - PLATFORM_OFFSET_X &&
           getPosition().y - getRadius() < platform.getPosition().y + PLATFORM_OFFSET_Y + platform.getSize().height;
}

void Meteorite::updateCollidedWithPlatforms(std::vector<Platform> &platforms)
{
    for (Platform &platform: platforms)
    {
        if (collidedWithPlatform(platform))
        {
            handleMeteoriteOverflow();
        }
    }
}

bool Meteorite::collidedWithLandscape(const sf::Vector2f firstPoint, const sf::Vector2f secondPoint) const
{
    if (secondPoint.x == firstPoint.x)
    {
        return getPosition().x + getRadius() > firstPoint.x &&
               getPosition().x - getRadius() < firstPoint.x &&
               getPosition().y + getRadius() > std::min(firstPoint.y, secondPoint.y) &&
               getPosition().y - getRadius() < std::max(firstPoint.y, secondPoint.y);
    }

    const float k = (secondPoint.y - firstPoint.y) / (secondPoint.x - firstPoint.x);
    const float b = firstPoint.y - k * firstPoint.x;

    const float vehicleCenterX = getPosition().x;
    const float vehicleBottomY = getPosition().y + getRadius();
    const float vehicleRightX = getPosition().x + getRadius();
    const float vehicleLeftX = getPosition().x - getRadius();

    return vehicleBottomY > k * vehicleCenterX + b &&
           vehicleRightX > firstPoint.x &&
           vehicleLeftX < secondPoint.x;
}

void Meteorite::updateCollidedWithLandscape(const std::vector<sf::Vector2f> &points)
{
    for (int i = 0; i < points.size() - 1; i++)
    {
        if (collidedWithLandscape(points[i], points[i + 1]))
        {
            handleMeteoriteOverflow();
        }
    }
}

sf::CircleShape Meteorite::getBody()
{
    return body;
}

sf::Vector2f Meteorite::getVelocity() const
{
    return velocity;
}

float Meteorite::getRadius() const
{
    return radius;
}

sf::Vector2f Meteorite::getPosition() const
{
    return body.getPosition();
}

void Meteorite::setPosition(const sf::Vector2f position)
{
    body.setPosition(position);
}

void Meteorite::setVelocity(const sf::Vector2f newVelocity)
{
    velocity = newVelocity;
}
