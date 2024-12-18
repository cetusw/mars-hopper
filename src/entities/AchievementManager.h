#ifndef ACHIEVEMENTMANAGER_H
#define ACHIEVEMENTMANAGER_H
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

class AchievementManager
{
public:
    AchievementManager();

    void initAchievementManager();

    void initNotification();

    bool isAchievementUnlocked(const std::string &achievement);

    void unlock(const std::string &achievement);

    void updateNotification();

    void drawAchievementNotification(sf::RenderWindow &window);

    std::string getLastAchievement();

    void setLastAchievement(const std::string &achievement);

    bool achievementUnlocked;
    float timeSinceLastUnlock;

private:
    std::string lastAchievement;
    sf::Clock clock;
    sf::Text achievementText;
    sf::Font font;
    sf::RectangleShape notificationBackground;
    float animationSpeed;
    std::vector<std::string> unlockedAchievements;
    std::ofstream outFile;
};


#endif //ACHIEVEMENTMANAGER_H
