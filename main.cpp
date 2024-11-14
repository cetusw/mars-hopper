#include <cmath>
#include <iostream>
#include <random>

#include <SFML/Graphics.hpp>

constexpr unsigned WINDOW_WIDTH = 1920;
constexpr unsigned WINDOW_HEIGHT = 1080;

constexpr float FREE_FALL_ACCELERATION = 3.7f;
constexpr float MAX_HOPPER_VELOCITY = 500.0f;

struct Size {
    float width;
    float height;
};

struct Hopper
{
    sf::Sprite body;
    sf::Vector2f velocity = {0, 0};
    sf::Vector2f acceleration = {0, 0};
    sf::Vector2f position;
    Size size = {150.f, 150.f};
};

struct Platform
{
    sf::ConvexShape body;
    sf::Vector2f position;
    Size size = {400.f, 50.f};
};

float getRandomNumber(const float min, const float max)
{
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_real_distribution distribution(min, max);

    return distribution(generator);
}

void loadTexture(sf::Texture &texture, const std::string &filePath)
{
    if (!texture.loadFromFile(filePath))
    {
        std::cerr << "Не удалось открыть файл" << std::endl;
    }
}

sf::Vector2f calculateHopperSize(const Hopper &hopper, const sf::Texture &texture) {
    const sf::Vector2u textureSize = texture.getSize();
    return {
        hopper.size.width / static_cast<float>(textureSize.x),
        hopper.size.height / static_cast<float>(textureSize.y)
    };
}

void initHopper(Hopper &hopper, sf::Texture &texture, const std::string &filePath)
{
    loadTexture(texture, filePath);

    const sf::Vector2f hopperSize = calculateHopperSize(hopper, texture);

    hopper.body.setScale(hopperSize);
    hopper.position = {400, 300};
    hopper.body.setTexture(texture);
    hopper.body.setOrigin(sf::Vector2f(0, 0));
}

void initPlatform(Platform &platform)
{
    platform.position = {getRandomNumber(0, WINDOW_WIDTH), getRandomNumber(0, WINDOW_HEIGHT)};
    platform.body.setPosition(platform.position);

    platform.body.setPointCount(4);
    platform.body.setPoint(0, {0, 0});
    platform.body.setPoint(1, {platform.size.width, 0});
    platform.body.setPoint(2, {platform.size.width, platform.size.height});
    platform.body.setPoint(3, {0, platform.size.height});

    platform.body.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
}

void initStartPlatform(Platform &platform)
{
    platform.position = {400, 300};
    platform.body.setPosition(platform.position);

    platform.body.setPointCount(4);
    platform.body.setPoint(0, {0, 0});
    platform.body.setPoint(1, {platform.size.width, 0});
    platform.body.setPoint(2, {platform.size.width, platform.size.height});
    platform.body.setPoint(3, {0, platform.size.height});

    platform.body.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
}

void initPlatforms(std::vector<Platform> &platform)
{
    Platform startPlatform, platform1, platform2;
    platform.emplace_back(platform1);
    platform.emplace_back(platform2);
    initStartPlatform(startPlatform);
    platform.emplace_back(startPlatform);
    for (Platform &onePlatform : platform)
    {
        initPlatform(onePlatform);
    }
}

void reduceAccelerationX(Hopper &hopper)
{
    constexpr float REDUCTION_RATE_X = 2.0f;

    if (hopper.acceleration.x > 0)
    {
        hopper.acceleration.x -= REDUCTION_RATE_X;
        if (hopper.acceleration.x < 0)
        {
            hopper.acceleration.x = 0;
        }
    }
    else if (hopper.acceleration.x < 0)
    {
        hopper.acceleration.x += REDUCTION_RATE_X;
        if (hopper.acceleration.x > 0)
        {
            hopper.acceleration.x = 0;
        }
    }
}

void reduceAccelerationY(Hopper &hopper)
{
    if (hopper.acceleration.y > 0)
    {
        hopper.acceleration.y -= FREE_FALL_ACCELERATION;
    }
    else
    {
        hopper.acceleration.y = 0;
    }
}

bool collidedWithPlatform(const Hopper &hopper, const Platform &platform)
{
    return !(hopper.position.y >= platform.position.y + platform.size.height ||
        (hopper.position.x + hopper.size.width <= platform.position.x ||
         hopper.position.x >= platform.position.x + platform.size.width ||
         hopper.position.y + hopper.size.height <= platform.position.y));
}

void updateCollide(std::vector<Platform> &platforms, Hopper &hopper, const float deltaTime)
{
    bool collided = false;

    for (Platform &onePlatform : platforms)
    {
        if (collidedWithPlatform(hopper, onePlatform))
        {
            collided = true;
            hopper.position.y = onePlatform.position.y - hopper.size.height;
            break;
        }
    }
    if (collided)
    {
        hopper.velocity = {0, 0};
        hopper.acceleration = {0, 0};
    }
    else
    {
        hopper.position += hopper.velocity * deltaTime;
        std::cout << hopper.position.y << std::endl;
    }
}

void updateHopperElements(Hopper &hopper)
{
    hopper.body.setPosition(hopper.position);
}

void updateHopperPosition(const float deltaTime, Hopper &hopper, std::vector<Platform> &platforms)
{
    hopper.velocity.x += hopper.acceleration.x;
    hopper.velocity.y += FREE_FALL_ACCELERATION - hopper.acceleration.y;

    reduceAccelerationX(hopper);
    reduceAccelerationY(hopper);

    updateCollide(platforms, hopper, deltaTime);

    updateHopperElements(hopper);
}

void pollEvents(sf::RenderWindow &window, Hopper &hopper)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Up)
                {
                    hopper.acceleration.y += 70.0f;
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    hopper.acceleration.x += 30.0f;
                    hopper.acceleration.y += 70.0f;
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    hopper.acceleration.x += -30.0f;
                    hopper.acceleration.y += 70.0f;
                }
            break;
            default:
                break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, const Hopper &hopper, std::vector<Platform> &platforms)
{
    window.clear(sf::Color(0x00, 0x00, 0x00));
    window.draw(hopper.body);
    for (Platform &onePlatform : platforms)
    {
        window.draw(onePlatform.body);
    }
    window.display();
}

int main()
{
    sf::Clock clock;

    sf::ContextSettings settings;
    //вынести в константу
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Mars Hopper", sf::Style::Default, settings);

    Hopper hopper;
    std::vector<Platform> platforms;

    sf::Texture hopperTexture;
    initHopper(hopper, hopperTexture, "../assets/crew-dragon.png");
    initPlatforms(platforms);

    while (window.isOpen())
    {
        const float deltaTime = clock.restart().asSeconds();

        pollEvents(window, hopper);
        updateHopperPosition(deltaTime, hopper, platforms);
        redrawFrame(window, hopper, platforms);
    }
}
