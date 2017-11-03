#include "entity.h"

#include "game.h"

Entity::Entity(Game &game, Vec2 pos, std::string sprite_set_filename)
    : game(game), pos(pos) {
    sprite_set = game.getResourceLoader().loadSpriteSet(sprite_set_filename);
}

void Entity::move(Vec2 v) {
    pos += v;
}

void Entity::update() {}
