#include <iostream>
#include <SFML/Audio/SoundBuffer.hpp>

void loadSound(sf::SoundBuffer &buffer, const std::string &filePath)
{
    if (!buffer.loadFromFile(filePath))
    {
        std::cerr << "Не удалось открыть файл со звуком" << std::endl;
    }
}
