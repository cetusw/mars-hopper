#include "RepairKitIndicator.h"
#include "../utils/utils.cpp"
#include "../utils/constants.h"

RepairKitIndicator::RepairKitIndicator(): repairKitIndicatorSize{REPAIR_KIT_INDICATOR_SIZE}, isDrawable(false)
{
}

void RepairKitIndicator::init()
{
    loadTexture(repairKitIndicatorTexture, REPAIR_KIT_TEXTURE_PATH);
    repairKitIndicatorSprite.setTexture(repairKitIndicatorTexture);
    repairKitIndicatorSprite.setScale(
        repairKitIndicatorSize.width / static_cast<float>(repairKitIndicatorTexture.getSize().x),
        repairKitIndicatorSize.height / static_cast<float>(repairKitIndicatorTexture.getSize().y)
    );
    repairKitIndicatorSprite.setOrigin(
        static_cast<float>(repairKitIndicatorTexture.getSize().x) / 2.0f,
        static_cast<float>(repairKitIndicatorTexture.getSize().y) / 2.0f
    );
    repairKitIndicatorSprite.setPosition({WINDOW_WIDTH - repairKitIndicatorSize.width, WINDOW_HEIGHT - repairKitIndicatorSize.height});
    isDrawable = false;
}

bool RepairKitIndicator::getDrawability() const
{
    return isDrawable;
}

sf::Sprite RepairKitIndicator::getSprite()
{
    return repairKitIndicatorSprite;
}

void RepairKitIndicator::setDrawability(const bool state)
{
    isDrawable = state;
}
