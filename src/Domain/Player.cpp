#include "Player.h"

Player::Player(int minX, int minY, int maxX, int maxY): minX(minX), minY(minY), maxX(maxX), maxY(maxY) {
    x = minX;
    y = minY;
}

void Player::moveX(int direction) {
        std::lock_guard<std::mutex> lock(playerMutex);
        int delta = MOVE_SPEED * direction;

        if (x + delta >= maxX || x + delta <= minX) {
            return;
        }

        x += delta;
}

void Player::moveY(int direction) {
        std::lock_guard<std::mutex> lock(playerMutex);
        int delta = MOVE_SPEED * direction;
        if (y + delta >= maxY || y + delta <= minY) {
            return;
        }

        y += delta;
}

int Player::getX() {
    std::lock_guard<std::mutex> lock(playerMutex);
    return x;
}

int Player::getY() {
    std::lock_guard<std::mutex> lock(playerMutex);
    return y;
}

void Player::jump() {
    if (!grounded) {
        return;
    }
    grounded = false;
    acceleration = -15;
}

void Player::pullDown() {
    if (y == maxY && acceleration == 0) {
        return;
    }

    if (y + acceleration > maxY) {
        acceleration = 0;
        y = maxY;
        grounded = true;
        return;
    }

    y += acceleration++;
}

bool Player::isGrounded() {
    return grounded;
}
