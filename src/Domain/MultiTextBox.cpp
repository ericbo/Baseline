#include <Domain/MultiTextBox.h>

MultiTextBox::MultiTextBox(const std::vector<std::pair<std::string, Text>> &map) : map(map) {}

void MultiTextBox::update(const std::string &name, const std::string &content) {
    int index = find(name);
    if (index == -1) {
        return;
    }
    
    map[index].second.update(content);
}

void MultiTextBox::draw(sf::RenderWindow &window, int x, int y) {
    for (auto &text : map) {
        const auto &size = text.second.getSize();
        text.second.draw(window, x, y);
        y += size.second + 5;
    }
}

int MultiTextBox::find(const std::string &name) {
    for (int i = 0; i < map.size(); i++) {
        if (map[i].first == name) {
            return i;
        }
    }

    return -1;
}