#include "entity.h"

#include "game.h"

Entity::Entity(Game &game, Vec2 pos, std::string sprite_set_filename)
    : game(game), pos(pos),hp(100),timer(sprite_set_filename) {
    sprite_set = game.getResourceLoader().loadSpriteSet(sprite_set_filename);

}

Entity::Entity(Game &game, Vec2 pos, std::string sprite_set_filename,const int hp)
        : game(game), pos(pos),hp(100),timer(sprite_set_filename) {
    sprite_set = game.getResourceLoader().loadSpriteSet(sprite_set_filename);
}


void Entity::move(Vec2 v) {
    pos += v;
}

void Entity::damage(int hp) {
    this->hp-=hp;
}

bool Entity::equals(const Entity* other){
    return this==other;
}


void Entity::update() {}
