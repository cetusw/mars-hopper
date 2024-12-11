#ifndef PASSEDPLATFORMS_H
#define PASSEDPLATFORMS_H
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>


class PassedPlatforms {
public:
    PassedPlatforms();
    void init();
    void update(const std::vector<int> &passedPlatforms);

    sf::Text platformsText;

private:
    sf::Font font;
};



#endif //PASSEDPLATFORMS_H
