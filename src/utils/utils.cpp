#include <iostream>
#include <random>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Texture.hpp>

inline float getRandomNumber(const float min, const float max)
{
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_real_distribution distribution(min, max);
    return distribution(generator);
}

inline void loadSound(sf::SoundBuffer &buffer, const std::string &filePath)
{
    if (!buffer.loadFromFile(filePath))
    {
        std::cerr << "Не удалось открыть файл со звуком" << std::endl;
    }
}

inline void loadFont(sf::Font &font, const std::string &filePath)
{
    if (!font.loadFromFile(filePath))
    {
        std::cerr << "Не удалось загрузить шрифт" << std::endl;
    }
}

inline void loadTexture(sf::Texture &texture, const std::string &filePath)
{
    if (!texture.loadFromFile(filePath))
    {
        std::cerr << "Не удалось загрузить текстуру" << std::endl;
    }
}
