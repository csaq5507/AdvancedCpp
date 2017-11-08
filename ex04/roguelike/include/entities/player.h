#ifndef ROGUELIKE_ENTITIES_PLAYER_H_
#define ROGUELIKE_ENTITIES_PLAYER_H_

#include "entity.h"

enum Weapon{melee, flint};

class Player : public Entity {
private:
    Weapon weapon;
    std::chrono::time_point<std::chrono::high_resolution_clock> attack_timer;
public:
    Player(Game &game, Vec2 pos);
    Player(Game &game, Vec2 pos, const int hp);

    void update() override;

    void attack();
};

#endif  // ROGUELIKE_ENTITIES_PLAYER_H_
