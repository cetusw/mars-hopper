#include "AchievementManager.h"
#include "../utils/constants.h"
#include "../utils/utils.cpp"
#include <fstream>
#include <iostream>
#include <ostream>

AchievementManager::AchievementManager(): achievementUnlocked(false), timeSinceLastUnlock(0.0f), animationSpeed(ACHIEVEMENT_FONT_SIZE)
{
}

void AchievementManager::initAchievementManager()
{
    outFile = loadFileForAppend(ACHIEVEMENTS_FILE);
    unlockedAchievements.clear();
    std::ifstream inFile = loadFileForRead(ACHIEVEMENTS_FILE);
    std::string line;
    while (std::getline(inFile, line))
    {
        unlockedAchievements.emplace_back(line);
    }
}

void AchievementManager::initNotification()
{
    animationSpeed = ACHIEVEMENT_SHOW_TIME;

    notificationBackground.setSize(ACHIEVEMENT_SIZE);
    notificationBackground.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    notificationBackground.setOrigin(notificationBackground.getSize().x / 2, notificationBackground.getSize().y / 2);
    notificationBackground.setPosition(ACHIEVEMENT_START_POSITION);

    loadFont(font, BOLD_FONT);
    achievementText.setFont(font);
    achievementText.setCharacterSize(ACHIEVEMENT_FONT_SIZE);
    achievementText.setFillColor(sf::Color::Black);
}

void AchievementManager::unlock(const std::string &achievement)
{
    if (isAchievementUnlocked(achievement))
    {
        return;
    }

    timeSinceLastUnlock = 0.0f;
    achievementUnlocked = true;
    achievementText.setString(achievement);
    achievementText.setOrigin(achievementText.getGlobalBounds().width / 2, achievementText.getGlobalBounds().height / 2);
    achievementText.setPosition(notificationBackground.getPosition().x, notificationBackground.getPosition().y);
    outFile << achievement << std::endl;
}

void AchievementManager::updateNotification()
{
    const float deltaTime = clock.restart().asSeconds();
    timeSinceLastUnlock += deltaTime;

    if (timeSinceLastUnlock > ACHIEVEMENT_SHOW_TIME && achievementUnlocked)
    {
        timeSinceLastUnlock = 0.0f;
        achievementUnlocked = false;
        notificationBackground.setPosition(ACHIEVEMENT_START_POSITION);
        achievementText.setPosition(notificationBackground.getPosition().x, notificationBackground.getPosition().y);
        animationSpeed = ACHIEVEMENT_ANIMATION_SPEED;
    }
}

bool AchievementManager::isAchievementUnlocked(const std::string &achievement)
{
    for (std::string &unlockedAchievement : unlockedAchievements)
    {
        if (unlockedAchievement == achievement)
        {
            return true;
        }
    }
    return false;
}

void AchievementManager::drawAchievementNotification(sf::RenderWindow &window)
{
    if (!achievementUnlocked)
    {
        return;
    }
    animationSpeed *= ACHIEVEMENT_ANIMATION_ACCELERATION;
    if (notificationBackground.getPosition().x > WINDOW_WIDTH - notificationBackground.getSize().x / 2)
    {
        notificationBackground.setPosition(notificationBackground.getPosition().x - animationSpeed * TIME_STEP, notificationBackground.getPosition().y);
        achievementText.setPosition(achievementText.getPosition().x - animationSpeed * TIME_STEP, notificationBackground.getPosition().y);
    }
    else
    {
        notificationBackground.setPosition(ACHIEVEMENT_END_POSITION);
        achievementText.setPosition(ACHIEVEMENT_END_POSITION);
    }
    window.draw(notificationBackground);
    window.draw(achievementText);
}

std::string AchievementManager::getLastAchievement()
{
    return lastAchievement;
}

void AchievementManager::setLastAchievement(const std::string &achievement)
{
    lastAchievement = achievement;
}
