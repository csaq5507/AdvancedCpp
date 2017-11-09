//
// Created by ivan on 09/11/17.
//

#ifndef ROGUELIKE_ENTITIES_PROJECTILE_H_
#define ROGUELIKE_ENTITIES_PROJECTILE_H_

#include "entity.h"

enum Projectile_Type{hitscan, projectile};

class Projectile : public Entity {
private:
    Projectile_Type type;
    std::chrono::time_point<std::chrono::high_resolution_clock> travel_timer;
public:
    Projectile(Game &game, Vec2 pos, Projectile_Type type);

    void update() override;

    void render(SDL_Renderer* renderer,Camera c);

    void attack();
};

#endif  // ROGUELIKE_ENTITIES_PROJECTILE_H_

