#include "PassedPlatforms.h"
#include "../utils/utils.cpp"
#include "../utils/constants.h"

PassedPlatforms::PassedPlatforms()
= default;

void PassedPlatforms::init()
{
    loadFont(font, BOLD_FONT);
    platformsText.setFont(font);
    platformsText.setCharacterSize(100);
    platformsText.setFillColor(sf::Color::White);
    platformsText.setPosition(PASSED_PLATFORMS_POSITION);
    platformsText.setString("0");
}

void PassedPlatforms::update(const std::vector<int> &passedPlatforms)
{
    const std::string newPlatformsNumber = std::to_string(passedPlatforms.size());
    platformsText.setString(newPlatformsNumber);
}