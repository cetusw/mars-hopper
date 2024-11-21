#ifndef GAMEBACKGROUND_H
#define GAMEBACKGROUND_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


class GameBackground
{
public:
    GameBackground();

    void init(const std::string &filePath);

    sf::Sprite getBackgroundSprite();

private:
    sf::Sprite background;
    sf::Texture texture;
};


#endif //GAMEBACKGROUND_H
