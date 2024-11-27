#include "LoadTexture.h"

#include <iostream>

void loadTexture(sf::Texture &texture, const std::string &filePath)
{
    if (!texture.loadFromFile(filePath))
    {
        std::cerr << "Не удалось загрузить текстуру" << std::endl;
    }
}