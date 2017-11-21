#ifndef __WEAPON__
#define __WEAPON__

#define _USE_MATH_DEFINES
#include <vector>
#include "enviorment_variables.h"
#include "utils/vec2.h"
#include "utils/chrono_timer.h"
#include <cmath>

enum WeaponTextType { melee, flint, pumpgun };
static constexpr double factor = M_PI / 180;

class Weapon {
	std::vector<Vec2> relativeHitFields;
	long long lastShotAt;
	long reloadTimeInMs;
	int dmg;
	WeaponTextType type;
public:

	static Weapon Melee();
	static Weapon Flint();
	static Weapon Pumpgun();
	std::vector<Vec2> GetHitedFields(Direction d);
	int GetDmg();
	bool readyToShoot();
	void updateShotTimer();
	WeaponTextType GetTexType();
};


#endif // !__WEAPON__