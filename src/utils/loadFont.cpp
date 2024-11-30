#include <iostream>
#include <SFML/Graphics/Font.hpp>

void loadFont(sf::Font& font, const std::string &filePath)
{
    if (!font.loadFromFile(filePath))
    {
        std::cerr << "Не удалось загрузить шрифт" << std::endl;
    }
}
