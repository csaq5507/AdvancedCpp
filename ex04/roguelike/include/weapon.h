#ifndef __WEAPON__
#define __WEAPON__

#define _USE_MATH_DEFINES
#include <vector>
#include "enviorment_variables.h"
#include "utils/vec2.h"
#include "utils/chrono_timer.h"
#include "sprite_set.h"
#include <cmath>
#include <memory>

enum WeaponTextType { melee, flint, pumpgun };
static constexpr double factor = M_PI / 180;

class Weapon {
	std::vector<Vec2> relativeHitFields;
	long long lastShotAt;
	long reloadTimeInMs;
	int dmg;
	WeaponTextType type;
	std::string sprite_set_filename;
	int consumes_ammo;

public:

	Weapon() : lastShotAt(0), consumes_ammo(0) {};

	static Weapon Melee();
	static Weapon Flint();
	static Weapon Pumpgun();
	std::vector<Vec2> GetHitedFields(Direction d);
	int GetDmg();
	bool readyToShoot();
	void updateShotTimer();
	int ammo_consumption() {return consumes_ammo; };
	WeaponTextType GetTexType();
	std::string getSpriteSet() {
		return sprite_set_filename;
	}

};


#endif // !__WEAPON__