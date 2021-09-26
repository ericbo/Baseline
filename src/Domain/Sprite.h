#pragma once

#include <vector>
#include <chrono>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Sprite {
public:
    Sprite(
            const std::string &filename,
            int width,
            int height,
            int marginTop,
            int marginRight,
            int marginBottom,
            int marginLeft,
            int spacingRight,
            int spacingDown,
            int limitWidth,
            int limitHeight
    );

    void draw(sf::RenderWindow &window, int x, int y);
    void setAnimation(const std::vector<int> &squares);
    void mirror();
    void restore();

private:
    const std::string filename;
    const int width;
    const int height;
    const int marginTop;
    const int marginRight;
    const int marginBottom;
    const int marginLeft;
    const int spacingRight;
    const int spacingDown;
    const int limitWidth;
    const int limitHeight;

    std::vector<int> animation;
    int animationIndex;

    sf::Texture texture;
    sf::Sprite sprite;
    int tableWidth = 0;
    int tableHeight = 0;

    bool mirrored = false;

    int x = 0;
    int y = 0;
    std::chrono::steady_clock::time_point lastAnimation = std::chrono::steady_clock::now();

    void setNextTexture();
};


