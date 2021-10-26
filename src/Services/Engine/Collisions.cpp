
#include <vector>
#include "Collisions.h"

Collisions::Collisions(
        const std::vector<Player> &players,
        const std::vector<Projectile> &projectiles
) :
        players(players),
        projectiles(projectiles)
{}

void Collisions::calculate() {

}
