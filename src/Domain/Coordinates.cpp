#include "Coordinates.h"

#include <cmath>

Coordinates::Coordinates(int x, int y) : x(x), y(y) {}

bool Coordinates::equal(const Coordinates &coordinates) {
    return x == coordinates.getX() && y == coordinates.getY();
}

double Coordinates::calculateDistance(const Coordinates &coordinates) {
    return sqrt(pow(coordinates.getX() - x, 2) + pow(coordinates.getY() - y, 2));
}

int Coordinates::getX() const {
    return x;
}

int Coordinates::getY() const {
    return y;
}
