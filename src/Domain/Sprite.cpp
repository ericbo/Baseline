#include <Domain/Sprite.h>
#include <iostream>

Sprite::Sprite(
        const std::string &filename,
        const int width,
        const int height,
        const int marginTop,
        const int marginRight,
        const int marginBottom,
        const int marginLeft,
        const int spacingRight,
        const int spacingDown,
        const int limitWidth,
        const int limitHeight
) :
        filename(filename),
        width(width),
        height(height),
        marginTop(marginTop),
        marginRight(marginRight),
        marginBottom(marginBottom),
        marginLeft(marginLeft),
        spacingRight(spacingRight),
        spacingDown(spacingDown),
        limitHeight(limitHeight),
        limitWidth(limitWidth)
{
    if (!texture.loadFromFile(filename, sf::IntRect(0, 0, width, height)))
    {
        std::runtime_error("Failed to load in sprite from file " + filename + ".");
    }

    texture.setSmooth(true);

    tableWidth = width / (limitWidth + spacingRight);
    tableHeight = height / (limitHeight + spacingDown);

    y = marginTop;
    x = marginLeft;

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(marginLeft, marginTop,  limitWidth, limitHeight));
    sprite.setOrigin(sf::Vector2f(0, (float)limitHeight));
}

void Sprite::draw(sf::RenderWindow &window, int x, int y) {
    sprite.setPosition(sf::Vector2f((float)x, y));
    setNextTexture();
    window.draw(sprite);
}

void Sprite::setAnimation(const std::vector<int> &squares) {
    animation = squares;
    animationIndex = 0;
}

void Sprite::setNextTexture() {
    if (animation.empty()) {
        return;
    }

    int box = animation[animationIndex];
    int col = box % tableWidth;
    int row = box / tableHeight;

    if (animationIndex < animation.size() - 1) {
        animationIndex++;
    } else {
        animationIndex = 0;
    }

    int x = (limitWidth + spacingRight) * col + marginLeft;
    int y = (limitHeight + spacingDown) * row + marginTop;

    sprite.setTextureRect(sf::IntRect(x, y,  limitWidth, limitHeight));
}
