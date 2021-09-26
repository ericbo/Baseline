#include <Domain/Sprite.h>

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

void Sprite::setAnimation(const std::vector<int> &squares, int speed) {
    setAnimation(squares, Animation::REPEAT);
    animationSpeed = speed;
}

void Sprite::setAnimation(const std::vector<int> &squares, const Sprite::Animation &animation) {
    this->animation = animation;
    animationSequence = squares;
    sequenceIndex = 0;
}

void Sprite::mirror() {
    if (!mirrored) {
        sprite.scale(-1, 1);
        sprite.setOrigin(sf::Vector2f((float)limitWidth, (float) limitHeight));
        mirrored = true;
    }
}

void Sprite::restore() {
    if (mirrored) {
        sprite.scale(-1, 1);
        sprite.setOrigin(sf::Vector2f(0, (float) limitHeight));
        mirrored = false;
    }
}

void Sprite::setNextTexture() {
    if (animationSequence.empty()) {
        return;
    }

    if (animation == Animation::SINGLE && sequenceIndex == animationSequence.size() - 1) {
        return;
    }

    const auto &now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastAnimation).count();

    if (elapsed < animationSpeed) {
        return;
    }
    lastAnimation = now;

    int box = animationSequence[sequenceIndex];
    int col = box % tableWidth;
    int row = box / tableHeight;

    if (sequenceIndex < animationSequence.size() - 1) {
        sequenceIndex++;
    } else {
        sequenceIndex = 0;
    }

    int x = (limitWidth + spacingRight) * col + marginLeft;
    int y = (limitHeight + spacingDown) * row + marginTop;

    sprite.setTextureRect(sf::IntRect(x, y,  limitWidth, limitHeight));
}
