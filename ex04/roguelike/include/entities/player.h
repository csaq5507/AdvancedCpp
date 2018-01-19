#ifndef ROGUELIKE_ENTITIES_PLAYER_H_
#define ROGUELIKE_ENTITIES_PLAYER_H_

#include "entity.h"
#include "entities/enemy.h"
#include "weapon.h"
#include "Potion.h"


class Player : public Entity {
private:
    /* Weapon::Flint(), Weapon::Pumpgun() */
	std::vector<std::shared_ptr<Weapon>> equipedWeapons = std::vector<std::shared_ptr<Weapon>>(3);
	std::vector<std::shared_ptr<Entity>> inventory = std::vector<std::shared_ptr<Entity>>(5);
	int inventory_space = 0;
	int weaponIndex = 0;
	double strength = 1;

public:
    Player(Game &game, Vec2 pos);
    Player(Game &game, Vec2 pos, const int hp);

    void update() override;

    void render(SDL_Renderer* renderer, const Vec2& cameraPos);

	void attack();
	void throw_grenade();
	void use_potion(PotionType type);

    void damage(int hp) override;

	void serialize(std::fstream& f);
	static Player deserialize(std::fstream& f, Game& game);
    int getWeaponIndex();
    int getHP();
	std::vector<std::shared_ptr<Entity>> get_inventory(){ return inventory; }
    bool isWeaponAvailable(WeaponTextType weapon);
};

#endif  // ROGUELIKE_ENTITIES_PLAYER_H_
