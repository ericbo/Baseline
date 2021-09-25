#include <Domain/Text.h>

Text::Text(sf::Font &font, int size, sf::Color color) {
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(color);
}

void Text::update(const std::string &content) {
    text.setString(content);
}

std::pair<int, int> Text::getSize() {
    return {text.getLocalBounds().width, text.getLocalBounds().height};
}

void Text::draw(sf::RenderWindow &window, int x, int y) {
    text.setPosition((float)x - text.getLocalBounds().width - 5, (float)y);
    window.draw(text);
}
