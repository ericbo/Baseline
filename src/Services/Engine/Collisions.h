#pragma once

#include <vector>
#include <memory>

#include <Domain/Player.h>
#include <Domain/Projectile.h>

class Collisions {
public:
    Collisions(const std::vector<Player> &players, const std::vector<Projectile> &projectiles);
    void calculate();
private:
    const std::vector<Player> players;
    const std::vector<Projectile> projectiles;
};