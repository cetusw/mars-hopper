#include "TextureLoader.h"

#include <iostream>

void TextureLoader::loadTexture(sf::Texture &texture, const std::string &filePath)
{
    if (!texture.loadFromFile(filePath)) // нет смысла создавать класс ради 3 строчек кода
    {
        std::cerr << "Не удалось открыть файл" << std::endl;
    }
}
