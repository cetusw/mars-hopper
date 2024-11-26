#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../utils/GameState.h"

class MainMenu {
public:
    MainMenu();
    void draw(sf::RenderWindow &window);
    void handleInput(sf::Event event);
    void handleMainMenu(sf::RenderWindow &window, GameState &state);
    int getSelectedOption() const;

private:
    void init();

    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> options;
    int selectedOption;
};

#endif //MAINMENU_H
