#include "weapon.h"
#include "game.h"
#include <iostream>

bool Weapon::readyToShoot() {
	if (lastShotAt + reloadTimeInMs < Game::timer.get_elapsed_time()) return true;
	return false;
}
void Weapon::updateShotTimer() {
	lastShotAt = Game::timer.get_elapsed_time();
}

WeaponTextType Weapon::GetTexType() {
	return this->type;
}

void roatation(Vec2& toRotate, double angleInRad) {
	int tmpx = lround(toRotate.x * cos(angleInRad) - toRotate.y * sin(angleInRad));
	toRotate.y = lround(toRotate.x * sin(angleInRad) + toRotate.y * cos(angleInRad));
	toRotate.x = tmpx;
}

std::vector<Vec2> Weapon::GetHitedFields(Direction d) {
	std::vector<Vec2> result{this->relativeHitFields.begin(), this->relativeHitFields.end()};
	double angle;
	switch (d){
	case north: angle = 90;
		break;
	case west: angle = 180;
		break;
	case south: angle = 270;
		break;
	case east: angle = 0;
		return result;
	}
	angle = angle * factor;
	for(auto& v : result) {
		roatation(v, angle);
	}
	return result;
}

Weapon Weapon::Melee() {
	Weapon w;
	w.sprite_set_filename = "sword.png";

	w.relativeHitFields.push_back(Vec2{ 1, -1 });
	w.relativeHitFields.push_back(Vec2{ 1, 0 });
	w.relativeHitFields.push_back(Vec2{ 1, 1 });
	w.dmg = 100;
	w.reloadTimeInMs = 500;
	w.type = melee;
	return w;
}
Weapon Weapon::Flint() {
	Weapon w;
	w.sprite_set_filename = "pistol.png";
	for (int i = 1; i <= 20;i++) {
		w.relativeHitFields.push_back(Vec2({ i,0 }));
	}
	w.dmg = 50;
	w.reloadTimeInMs = 100;
	w.type = flint;
	
	return w;
}

Weapon Weapon::Pumpgun() {
	Weapon w;
	w.sprite_set_filename = "shotgun.png";
	for (int i = 1;i <= 8;i++)
		w.relativeHitFields.push_back(Vec2({ i,0 }));

	for (int i = 3;i <= 8;i++) {
		w.relativeHitFields.push_back(Vec2({ i, -1 }));
		w.relativeHitFields.push_back(Vec2({ i, 1 }));
	}

	for (int i = 6;i <= 8;i++) {
		w.relativeHitFields.push_back(Vec2({ i, -2 }));
		w.relativeHitFields.push_back(Vec2({ i, 2 }));
	}
	w.dmg = 25;
	w.reloadTimeInMs = 1000;
	w.type = pumpgun;
	return w;
}

int Weapon::GetDmg() {
	return this->dmg;
}