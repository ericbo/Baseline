#pragma once

#include <string>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Text {
public:
    Text(sf::Font &font, int size, sf::Color color);
    void update(const std::string &content);
    std::pair<int, int> getSize();
    void draw(sf::RenderWindow &window, int x, int y);

private:
    sf::Text text;
};


