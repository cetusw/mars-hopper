#include "GameBackground.h"

#include "../utils/Constants.h"
#include "../utils/TextureLoader.h"

GameBackground::GameBackground()
= default;

void GameBackground::init(const std::string &filePath)
{
    TextureLoader::loadTexture(texture, filePath);
    background.setTexture(texture);
    background.setScale(
        WINDOW_WIDTH / background.getLocalBounds().width,
        WINDOW_HEIGHT / background.getLocalBounds().height
    ); // мало логики
}

sf::Sprite GameBackground::getBackgroundSprite()
{
    return background;
}
