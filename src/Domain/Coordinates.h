#pragma once


class Coordinates {
public:
    Coordinates(int x, int y);

    bool equal(const Coordinates &coordinates);
    double calculateDistance(const Coordinates &coordinates);

    int getX() const;
    int getY() const;

private:
    int x;
    int y;
};


