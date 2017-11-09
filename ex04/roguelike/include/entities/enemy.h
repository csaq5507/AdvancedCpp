#ifndef ROGUELIKE_ENTITIES_ENEMY_H_
#define ROGUELIKE_ENTITIES_ENEMY_H_

#include "entity.h"
#include <random>
#include "entities/player.h"

class Enemy : public Entity {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> move_timer;

    std::default_random_engine rnd;
    std::uniform_int_distribution<int> rng;
    int speed;
    std::shared_ptr<Entity> player;

    int is_player_near();
    Vec2 get_player_direction();
public:
    Enemy(Game &game, Vec2 pos, std::shared_ptr<Entity> player);
    void render(SDL_Renderer* renderer, Camera c);
    void update() override;
};

#endif  // ROGUELIKE_ENTITIES_ENEMY_H_
