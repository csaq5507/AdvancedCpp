#ifndef ROGUELIKE_ENTITIES_ENEMY_H_
#define ROGUELIKE_ENTITIES_ENEMY_H_

#include "entity.h"

class Enemy : public Entity {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> move_timer;

public:
    Enemy(Game &game, Vec2 pos);

    void update() override;
};

#endif  // ROGUELIKE_ENTITIES_ENEMY_H_
