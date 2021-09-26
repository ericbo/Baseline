#pragma once

#include <mutex>

class Player {
public:
    enum direction {IDEL, LEFT, RIGHT};

public:
    explicit Player(int minX, int minY, int maxX, int maxY);

    void moveX(int direction);
    void moveY(int direction);
    int getX();
    int getY();
    void jump();
    void pullDown();
    bool isGrounded();
    direction getDirection();
    direction getLastDirection();
    void updateDirection();

private:
    static constexpr int MOVE_SPEED = 5;

    const int minX;
    const int minY;
    const int maxX;
    const int maxY;

    int x = 0;
    int y = 0;
    int lastX = 0;
    int lastY = 0;
    int updateCount = 0;
    direction lastDirection = direction::IDEL;
    int acceleration = 0;
    bool grounded = false;
    std::mutex playerMutex;
};
