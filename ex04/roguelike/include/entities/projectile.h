//
// Created by ivan on 09/11/17.
//

#ifndef ROGUELIKE_ENTITIES_PROJECTILE_H_
#define ROGUELIKE_ENTITIES_PROJECTILE_H_

#include "entity.h"
#include "entities/player.h"
class Projectile : public Entity {
private:
    long long existence_timer;
	WeaponTextType type;
public:
    Projectile(Game &game, Vec2 pos, WeaponTextType w_type, Direction dir);

    void update() override;

    void render(SDL_Renderer* renderer, const Vec2& cameraPos);
	void serialize(std::fstream& f);
	static Projectile deserialize(std::fstream& f, Game& game);
    void attack();
};

#endif  // ROGUELIKE_ENTITIES_PROJECTILE_H_

