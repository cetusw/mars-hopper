//
// Created by yogurt on 11/18/24.
//

#include "GameBackground.h"

#include "../utils/Constants.h"
#include "../utils/TextureLoader.h"

GameBackground::GameBackground()
{

}

void GameBackground::init(const std::string &filePath)
{
    TextureLoader::loadTexture(texture, filePath);
    background.setTexture(texture);
    background.setScale(
        WINDOW_WIDTH / background.getLocalBounds().width,
        WINDOW_HEIGHT / background.getLocalBounds().height
    );
}

sf::Sprite GameBackground::getBackgroundSprite()
{
    return background;
}
