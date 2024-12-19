#include "Meteorite.h"
#include "../utils/constants.h"
#include "../utils/utils.cpp"

Meteorite::Meteorite(): isFalling(false), direction(0), radius(METEORITE_RADIUS), velocity({0, 0})
{
}

void Meteorite::init()
{
    body.setRadius(radius);
    body.setOrigin(body.getRadius(), body.getRadius());
    body.setPosition(getRandomNumber(WINDOW_WIDTH + 1000, WINDOW_WIDTH + 2000), -800);
    body.setFillColor(sf::Color::Black);
    isFalling = false;
    flame.init(FLAME_IMAGE, METEORITE_FLAME_SIZE, {FRAME_WIDTH / 2, FRAME_HEIGHT - 20});
}

void Meteorite::addMeteorite(std::vector<Meteorite> &meteorites, float &timeSinceLastMeteorite)
{
    timeSinceLastMeteorite += TIME_STEP;

    if (timeSinceLastMeteorite < getRandomNumber(1, 3))
    {
        return;
    }

    sf::Vector2f startPosition;
    sf::Vector2f meteoriteVelocity;
    float direction;

    for (Meteorite &meteorite: meteorites)
    {
        if (getRandomNumber(0, 1) <= 0.5f)
        {
            startPosition = {getRandomNumber(WINDOW_WIDTH + 1000, WINDOW_WIDTH + 2000), -800};
            meteoriteVelocity = METEORITE_RIGHT_VELOCITY;
            direction = 1;
        }
        else
        {
            startPosition = {getRandomNumber(0, WINDOW_WIDTH), -800};\
            meteoriteVelocity = METEORITE_LEFT_VELOCITY;
            direction = -1;
        }

        timeSinceLastMeteorite = 0.0f;
        if (!meteorite.isFalling)
        {
            meteorite.setPosition(startPosition);
            meteorite.setVelocity(meteoriteVelocity);
            flame.getBody().setOrigin(meteorite.getPosition());
            meteorite.flame.setRotation(METEORITE_ANGEL * direction);
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
            updateFlame(meteorite);
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

void Meteorite::updateFlame(Meteorite &meteorite)
{
    meteorite.flame.isAnimating = true;
    meteorite.flame.update(9, 20);
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
    flame.setPosition({position.x, position.y});
}

void Meteorite::setVelocity(const sf::Vector2f newVelocity)
{
    velocity = newVelocity;
}
