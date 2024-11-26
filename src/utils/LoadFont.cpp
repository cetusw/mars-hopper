#include "LoadFont.h"

#include <iostream>

void loadFont(sf::Font& font, const std::string &filePath)
{
    if (!font.loadFromFile(filePath))
    {
        std::cerr << "Не удалось загрузить шрифт" << std::endl;
    }
}
