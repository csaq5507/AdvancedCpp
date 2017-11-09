#ifndef ROGUELIKE_ENTITIES_ENEMY_H_
#define ROGUELIKE_ENTITIES_ENEMY_H_

#include "entity.h"
#include <random>

class Enemy : public Entity {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> move_timer;

    std::default_random_engine rnd;
    std::uniform_int_distribution<int> rng;
public:
    Enemy(Game &game, Vec2 pos);
    void render(SDL_Renderer* renderer, Camera c);

    void update() override;
};

#endif  // ROGUELIKE_ENTITIES_ENEMY_H_
