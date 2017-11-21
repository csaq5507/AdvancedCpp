#include "entity.h"

#include "game.h"

Entity::Entity(Game &game, Vec2 pos, std::string sprite_set_filename)
    : game(game), pos(pos),hp(100),direction(Direction::south) {
    sprite_set = game.getResourceLoader().loadSpriteSet(sprite_set_filename);
    this->hp=100;
}

Entity::Entity(Game &game, Vec2 pos, std::string sprite_set_filename,const int hp)
        : game(game), pos(pos),hp(100),direction(Direction::south) {
    sprite_set = game.getResourceLoader().loadSpriteSet(sprite_set_filename);
    this->hp=hp;
}


bool Entity::move(int fields) {
    Vec2 v;
    switch (this->direction)
    {
        case Direction::north: v=Vec2(0,-fields); break;
        case Direction::east: v=Vec2(fields,0); break;
        case Direction::south: v=Vec2(0,fields); break;
        case Direction::west: v=Vec2(-fields,0); break;
    }
	if(!game.logic.checkMove(this->pos, v)) return false;
    this->pos += v;
	return true;
}

void Entity::damage(int hp) {
    this->hp-=hp;
}

bool Entity::equals(const Entity* other){
    return this==other;
}


void Entity::update() {}
