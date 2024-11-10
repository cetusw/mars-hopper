#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>

constexpr float FREE_FALL_SPEED = 3.7f;

struct Hopper
{
    sf::Sprite body;
    sf::Vector2f velocity;
    sf::Vector2f position;
};

void loadTexture(sf::Texture &texture, const std::string &filePath)
{
    if (!texture.loadFromFile(filePath))
    {
        std::cerr << "Не удалось открыть файл" << std::endl;
    }
}

void initHopper(Hopper &hopper, sf::Texture &texture, const std::string &filePath)
{
    loadTexture(texture, filePath);
    hopper.position = {400, 300};
    hopper.body.setTexture(texture);
    hopper.body.setOrigin(static_cast<sf::Vector2f>(texture.getSize()) / 2.0f);
}

void updateHopperElements(Hopper &hopper)
{
    hopper.body.setPosition(hopper.position);
}

void updatePosition(const float deltaTime, Hopper &hopper)
{
    const float motionLength = deltaTime * FREE_FALL_SPEED;

    hopper.position.y = hopper.position.y + motionLength;

    updateHopperElements(hopper);
}

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
            break;
            default:
                break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, const Hopper &hopper)
{
    window.clear(sf::Color(0x00, 0x00, 0x00));
    window.draw(hopper.body);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 1920;
    constexpr unsigned WINDOW_HEIGHT = 1080;
    sf::Clock clock;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Arrow follows mouse", sf::Style::Default, settings);

    Hopper hopper;

    sf::Texture hopperTexture;
    initHopper(hopper, hopperTexture, "../assets/crew-dragon.png");

    while (window.isOpen())
    {
        const float deltaTime = clock.restart().asSeconds();

        pollEvents(window);
        updatePosition(deltaTime, hopper);
        redrawFrame(window, hopper);
    }
}