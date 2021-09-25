#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>

#include <Domain/Text.h>

class MultiTextBox {
public:
    MultiTextBox(const std::vector<std::pair<std::string, Text>> &map);
    void update(const std::string &name, const std::string &content);
    void draw(sf::RenderWindow &window, int x, int y);
private:
    std::vector<std::pair<std::string, Text>> map;
    int find(const std::string &name);
};


