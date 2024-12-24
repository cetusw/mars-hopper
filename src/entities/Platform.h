#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>

#include "../utils/Size.h"

class Platform
{
public:
    Platform();

    void init(sf::Vector2f position);

    static void initEntity(sf::Vector2f position, Size size, sf::Sprite &sprite, sf::Texture &texture, const std::string &texturePath);

    void moveForward(std::vector<sf::Vector2f> &points);

    void updatePosition(const std::string &direction, const sf::Vector2f &velocity, std::vector<sf::Vector2f> &points);

    void updatePlatformsPosition(const std::string &direction, std::vector<sf::Vector2f> &points, std::vector<Platform> &platforms,
                                 sf::Vector2f velocity);

    float getPlatformPositionY(float x, std::vector<sf::Vector2f> &points);

    sf::Vector2f getPosition() const;

    Size getSize() const;

    sf::Sprite getBody();

    bool getRepairStatus() const;

    bool getRepairKitStatus() const;

    int getId() const;

    sf::Sprite getRepair();

    sf::Sprite getRepairKit();

    void setPosition(const sf::Vector2f &position);

    void setRepairStatus();

    void setRepairKitStatus();

    void setRepairKit(bool state);

    void setId();

private:
    int id;
    static int lastId;
    sf::Sprite platformSprite;
    sf::Texture platformTexture;
    Size platformSize;
    bool isRepair;
    sf::Sprite repairSprite;
    sf::Texture repairTexture;
    Size repairSize;
    sf::Sprite repairKitSprite;
    sf::Texture repairKitTexture;
    Size repairKitSize;
    float repairKitOffset;
    bool isRepairKit;
};

#endif //PLATFORM_H
