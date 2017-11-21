#ifndef ROGUELIKE_ENTITIES_PLAYER_H_
#define ROGUELIKE_ENTITIES_PLAYER_H_

#include "entity.h"
#include "entities/enemy.h"
#include "weapon.h"


class Player : public Entity {
private:
    int weaponIndex = 0;
	std::vector<Weapon> equipedWeapons{ Weapon::Melee(), Weapon::Flint(), Weapon::Pumpgun()};
    int movement_speed = 1;

public:
    Player(Game &game, Vec2 pos);
    Player(Game &game, Vec2 pos, const int hp);

    void update() override;

    void render(SDL_Renderer* renderer, const Vec2& cameraPos);

    void attack();

    void damage(int hp) override;
};

#endif  // ROGUELIKE_ENTITIES_PLAYER_H_
