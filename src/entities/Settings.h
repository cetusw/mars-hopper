#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../utils/GameState.h"

class Settings {
public:
    Settings();
    void draw(sf::RenderWindow &window);
    void handleInput(sf::Event event);
    void handleSettings(sf::RenderWindow &window, GameState &state);
    int getSelectedOption() const;

private:
    void init();

    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> options;
    int selectedOption;
};

#endif //SETTINGS_H
