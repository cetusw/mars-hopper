#include "Platform.h"
#include "../utils/utils.cpp"
#include "../utils/constants.h"
#include "../utils/GameDifficulty.h"

int Platform::lastId = 0;

Platform::Platform() : id(0), platformSize{PLATFORM_SIZE}, isRepair(false), repairSize{REPAIR_SIZE}, repairKitSize{REPAIR_KIT_SIZE},
                       repairKitOffset(0),
                       isRepairKit(false)
{
}

void Platform::init(const sf::Vector2f position, const GameDifficulty &difficulty)
{
    initEntity(position, platformSize, platformSprite, platformTexture, PLATFORM_TEXTURE_PATH);
    initEntity(position, repairSize, repairSprite, repairTexture, REPAIR_TEXTURE_PATH);
    repairKitOffset = getRandomNumber(-PLATFORM_SIZE.width / 2 + REPAIR_KIT_SIZE.width, PLATFORM_SIZE.width / 2 - REPAIR_KIT_SIZE.width);
    initEntity({position.x + repairKitOffset, position.y}, repairKitSize, repairKitSprite, repairKitTexture, REPAIR_KIT_TEXTURE_PATH);
    setRepairStatus(difficulty);
    setRepairKitStatus(difficulty);
    id = ++lastId;
}

void Platform::initEntity(const sf::Vector2f position, const Size size, sf::Sprite &sprite, sf::Texture &texture, const std::string &texturePath)
{
    loadTexture(texture, texturePath);
    sprite.setTexture(texture);
    sprite.setScale(
        size.width / static_cast<float>(texture.getSize().x),
        size.height / static_cast<float>(texture.getSize().y)
    );
    sprite.setOrigin(
        static_cast<float>(texture.getSize().x) / 2.0f,
        static_cast<float>(texture.getSize().y) / 2.0f
    );
    sprite.setPosition(position);
}

void Platform::moveForward(std::vector<sf::Vector2f> &points, const GameDifficulty &difficulty)
{
    if (getPosition().x + getSize().width < -WINDOW_WIDTH)
    {
        setPosition({
            WINDOW_WIDTH + WINDOW_EXPAND,
            getPlatformPositionY(WINDOW_WIDTH, points)
        });
        setRepairStatus(difficulty);
        setRepairKitStatus(difficulty);
        setId();
    }
}

void Platform::updatePosition(const std::string &direction, const sf::Vector2f &velocity, std::vector<sf::Vector2f> &points, const GameDifficulty &difficulty)
{
    if (direction == "horizontal")
    {
        setPosition({getPosition().x - velocity.x * TIME_STEP, getPosition().y});
    } else if (direction == "vertical")
    {
        setPosition({getPosition().x, getPosition().y - velocity.y * TIME_STEP});
    }
    moveForward(points, difficulty);
}

void Platform::updatePlatformsPosition(const std::string &direction, std::vector<sf::Vector2f> &points, std::vector<Platform> &platforms,
                                       const sf::Vector2f velocity, const GameDifficulty &difficulty)
{
    for (Platform &platform: platforms)
    {
        platform.updatePosition(direction, velocity, points, difficulty);
    }
}

void Platform::handleDifficulty(const GameDifficulty &difficulty, float &probability)
{
    switch (difficulty)
    {
        case GameDifficulty::Easy:
            probability = 0.4f;
        break;
        case GameDifficulty::Normal:
            probability = 0.6f;
        break;
        case GameDifficulty::Hard:
            probability = 0.8f;
        break;
        default:;
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
    return platformSprite.getPosition();
}

Size Platform::getSize() const
{
    return platformSize;
}

sf::Sprite Platform::getBody()
{
    return platformSprite;
}

bool Platform::getRepairStatus() const
{
    return isRepair;
}

bool Platform::getRepairKitStatus() const
{
    return isRepairKit;
}

int Platform::getId() const
{
    return id;
}

sf::Sprite Platform::getRepair()
{
    return repairSprite;
}


sf::Sprite Platform::getRepairKit()
{
    return repairKitSprite;
}

void Platform::setPosition(const sf::Vector2f &position)
{
    platformSprite.setPosition(position);
    repairSprite.setPosition({position.x, position.y - REPAIR_OFFSET});
    repairKitSprite.setPosition({position.x + repairKitOffset, position.y - REPAIR_KIT_OFFSET});
}

void Platform::setRepairStatus(const GameDifficulty &difficulty)
{
    float probability;
    handleDifficulty(difficulty, probability);
    isRepair = false;
    if (getRandomNumber(0, 1) > probability)
    {
        isRepair = true;
    }
}

void Platform::setRepairKitStatus(const GameDifficulty &difficulty)
{
    float probability;
    handleDifficulty(difficulty, probability);
    isRepairKit = false;
    if (getRandomNumber(0, 1) > probability && !isRepair)
    {
        isRepairKit = true;
    }
}

void Platform::setRepairKit(const bool state)
{
    isRepairKit = state;
}

void Platform::setId()
{
    id = ++lastId;
}
