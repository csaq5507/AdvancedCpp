#ifndef ROGUELIKE_ENTITY_H_
#define ROGUELIKE_ENTITY_H_

#include <memory>
#include <string>

#include "sprite_set.h"
#include "utils/vec2.h"
#include "chrono_timer.h"

class Game;

class Entity {
  protected:
    Game &game;
    Vec2 pos;
    std::shared_ptr<SpriteSet> sprite_set;
    int hp;
    ChronoTimer timer;

  public:
    Entity(Game &game, Vec2 pos, std::string sprite_set_filename);
    Entity(Game &game, Vec2 pos, std::string sprite_set_filename,const int hp);

    virtual ~Entity() = default;

    Vec2 getPos() const {
        return pos;
    }

    void setPos(Vec2 new_pos) {
        pos = new_pos;
    }

    void move(Vec2 pos);

    std::shared_ptr<SpriteSet> getSpriteSet() {
        return sprite_set;
    }

    virtual void update();
};

#endif  // ROGUELIKE_ENTITY_H_
