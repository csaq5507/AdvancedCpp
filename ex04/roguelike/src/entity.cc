#include "entity.h"
#include "game.h"
#include "SDL_mixer.h"

Entity::Entity(Game &game, Vec2 pos, std::string sprite_set_filename)
        : game(game),
          pos(pos),
          hp(100),
          movement_speed(0.5),
          direction(Direction::south),
          move_timer(0)
{
    sprite_set = game.getResourceLoader().loadSpriteSet(sprite_set_filename);
}

Entity::Entity(Game &game, Vec2 pos, std::string sprite_set_filename,const int hp)
        : game(game),
          pos(pos),
          hp(hp),
          movement_speed(0.5),
          direction(Direction::south),
          move_timer(0)
{
    sprite_set = game.getResourceLoader().loadSpriteSet(sprite_set_filename);
}

Entity::Entity(Game &game, Vec2 pos, std::string sprite_set_filename,const double movement_speed)
        : game(game),
          pos(pos),
          hp(100),
          movement_speed(movement_speed),
          direction(Direction::south),
          move_timer(0)
{
    sprite_set = game.getResourceLoader().loadSpriteSet(sprite_set_filename);
}

Entity::Entity(Game &game, Vec2 pos, std::string sprite_set_filename,const int hp,const double movement_speed)
        : game(game),
          pos(pos),
          hp(hp),
          movement_speed(movement_speed),
          direction(Direction::south),
          move_timer(0)
{
    sprite_set = game.getResourceLoader().loadSpriteSet(sprite_set_filename);
}


bool Entity::move() {
    if(Game::timer.get_elapsed_time() > move_timer) {
        long long int delay=( Game::timer.milliseconds(1000).count() / movement_speed );
        move_timer = Game::timer.get_elapsed_time() + ( (fast) ? delay/2 : delay ) ;
        Vec2 v;
        switch (this->direction) {
            case Direction::north:
                v = Vec2(0, -1);
                break;
            case Direction::east:
                v = Vec2(1, 0);
                break;
            case Direction::south:
                v = Vec2(0, 1);
                break;
            case Direction::west:
                v = Vec2(-1, 0);
                break;
        }
        if (!game.logic.checkMove(this->pos, v))
            return false;
        this->pos += v;
        return true;
    }
    return false;
}

void Entity::damage(int hp) {
    this->hp-=hp;
}

bool Entity::equals(const Entity* other){
    return this==other;
}

void Entity::update() {}

void Entity::serialize(std::fstream& f) {
	f << pos.x << std::endl;
	f << pos.y << std::endl;
	f << hp << std::endl;
	f << direction << std::endl;
}

int Entity::getHP() {
    return this->hp;
}