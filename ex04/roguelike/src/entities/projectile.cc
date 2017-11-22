#include "entities/projectile.h"

#include <SDL.h>

#include "enviorment_variables.h"

#include "game.h"
#include <vector>
#include <iostream>
#include <string>
#include "sprite_set.h"



Projectile::Projectile(Game& game, Vec2 pos, WeaponTextType w_type, Direction dir) : Entity(game, pos, ((w_type== WeaponTextType::melee)?"cheshirecat.png":((w_type== WeaponTextType::flint)?"will-o-wisp.png":"pumpkin.png"))), existence_timer(Game::timer.get_elapsed_time() + 200) {
	type = w_type;
	this->direction = dir;
    switch(this->direction) {
        case Direction::north: this->sprite_set->setRect(0, 3*tile_size,tile_size,tile_size); break;
        case Direction::south: this->sprite_set->setRect(0, 0, tile_size,tile_size); break;
        case Direction::east: this->sprite_set->setRect(0, 2*tile_size, tile_size,tile_size); break;
        case Direction::west: this->sprite_set->setRect(0, 1*tile_size, tile_size,tile_size); break;
    }
}

void Projectile::update() {
    if(Game::timer.get_elapsed_time() > existence_timer)
    {
        std::vector<Vec2> range;
        range.push_back(Vec2(this->getPos().x,this->getPos().y));
        this->hp=0;
    }
}


void Projectile::render(SDL_Renderer* renderer, const Vec2& cameraPos){
    SDL_Rect dst;
    dst.x = (this->getPos().x * tile_size ) - cameraPos.x;
    dst.y = (this->getPos().y * tile_size) - cameraPos.y;
    dst.w = tile_size;
    dst.h = tile_size;
    auto sprite_set = this->getSpriteSet();
    SDL_RenderCopy(renderer, sprite_set->getTexture(),
                   sprite_set->getRect(), &dst);
}


void Projectile::serialize(std::fstream& f) {
	f << projectile << std::endl;
	Entity::serialize(f);
	f << this->type << std::endl;
}
//convention type was already read
Projectile Projectile::deserialize(std::fstream& f, Game& game) {
	std::string line;
	Vec2 pos;
	int hp;
	Direction dir;
	std::getline(f, line);
	pos.x = std::stoi(line);
	std::getline(f, line);
	pos.y = std::stoi(line);
	std::getline(f, line);
	hp = std::stoi(line);
	std::getline(f, line);
	dir = (Direction)std::stoi(line);
	std::getline(f, line);
	WeaponTextType textType = (WeaponTextType)std::stoi(line);
	Projectile p(game, pos, textType, dir);
	p.hp = hp;
	return p;
}