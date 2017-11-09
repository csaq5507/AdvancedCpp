#include "entities/enemy.h"

#include <SDL.h>
#include <random>
#include "game.h"
#include "sprite_set.h"

Enemy::Enemy(Game& game, Vec2 pos) : Entity(game, pos, "player2.png"), move_timer(std::chrono::high_resolution_clock::now()) {
    sprite_set->setRect(0, 0, 0, 0/*SPRITE_SIZE, SPRITE_SIZE*/);
}

void Enemy::update() {

    if(timer.get_current_time()>move_timer) {
        move_timer = timer.get_current_time() + timer.one_second();
        std::default_random_engine rnd;
        std::uniform_int_distribution<int> rng(-1,2);
        std::uniform_int_distribution<int> rng2(0,2);
        move((rng2(rnd)==0)?Vec2({rng(rnd),0}):Vec2({0,rng(rnd)}));
    }
}
