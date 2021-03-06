#ifndef ROGUELIKE_ENTITY_H_
#define ROGUELIKE_ENTITY_H_

#include <memory>
#include <string>
#include <fstream>
#include "enviorment_variables.h"
#include "sprite_set.h"
#include "utils/vec2.h"
#include "utils/chrono_timer.h"
#include "logic/logic.h"

class Game;
enum EntityType { enemy, player, projectile};

class Entity {
  protected:
    Game &game;
    Vec2 pos;
    int hp;
    Direction direction;
    std::shared_ptr<SpriteSet> sprite_set;
    double movement_speed;
    long long move_timer;
    bool fast=false;

public:
    Entity(Game &game, Vec2 pos, std::string sprite_set_filename);
    Entity(Game &game, Vec2 pos, std::string sprite_set_filename, const int hp);
    Entity(Game &game, Vec2 pos, std::string sprite_set_filename, const double movement_speed);
    Entity(Game &game, Vec2 pos, std::string sprite_set_filename, const int hp, const double movement_speed);

    virtual ~Entity() = default;

    Vec2 getPos() const {
        return pos;
    }

    void setPos(Vec2 new_pos) {
        pos = new_pos;
    }

    bool move();

    std::shared_ptr<SpriteSet> getSpriteSet() {
        return sprite_set;
    }

    virtual void damage(int hp);

    bool is_dead(){
        return this->hp<=0;
    }

    virtual void update();

    virtual void render(SDL_Renderer* renderer, const Vec2& cameraPos) = 0;

	Vec2 getPixelCoordinate() {
		auto r = getPos();
		r.x *= tile_size;
		r.y *= tile_size;
		return r;
	}

    template<typename CheckType>
    bool isInstanceOf() {
        return (dynamic_cast<CheckType *>(this) != nullptr);
    }


    bool equals(const Entity* other);
	virtual void serialize(std::fstream& f);
};


#endif  // ROGUELIKE_ENTITY_H_
