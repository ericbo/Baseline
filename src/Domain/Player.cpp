#include "Player.h"

Player::Player(int minX, int minY, int maxX, int maxY): minX(minX), minY(minY), maxX(maxX), maxY(maxY) {
    x = minX;
    y = minY;
}

void Player::moveX(int direction) {
        if (attacking) {
            return;
        }
        std::lock_guard<std::mutex> lock(playerMutex);
        int delta = MOVE_SPEED * direction;

        if (x + delta >= maxX || x + delta <= minX) {
            return;
        }

        lastX = x;
        x += delta;
}

void Player::moveY(int direction) {
        std::lock_guard<std::mutex> lock(playerMutex);
        int delta = MOVE_SPEED * direction;
        if (y + delta >= maxY || y + delta <= minY) {
            return;
        }

        lastY = y;
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
    if (attacking) {
        return;
    }

    if (!grounded && !secondJump && acceleration >= 0) {
        acceleration = -15;
        secondJump = true;
    }

    if (!grounded) {
        return;
    }
    grounded = false;
    acceleration = -15;
}

void Player::attack() {
    attacking = true;
}

void Player::idle() {
    attacking = false;
}

void Player::pullDown() {
    if (y == maxY && acceleration == 0) {
        return;
    }

    if (y + acceleration > maxY) {
        acceleration = 0;
        lastY = y;
        y = maxY;
        grounded = true;
        secondJump = false;
        return;
    }

    lastY = y;
    y += acceleration++;
}

bool Player::isGrounded() {
    return grounded;
}

Player::state Player::getState() {
    if (attacking) {
        return ATTACK;
    }

    if (!grounded) {
        return JUMPING;
    }

    if (lastX == x) {
        return IDEL;
    }

    if (lastX > x) {
        return LEFT;
    }

    return RIGHT;
}

Player::state Player::getLastState() {
    return lastDirection;
}

void Player::updateState() {
    lastX = x;
    lastY = y;
}
