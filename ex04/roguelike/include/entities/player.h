#ifndef ROGUELIKE_ENTITIES_PLAYER_H_
#define ROGUELIKE_ENTITIES_PLAYER_H_

#include "entity.h"

class Player : public Entity {
  public:
    Player(Game &game, Vec2 pos);

    void update() override;
};

#endif  // ROGUELIKE_ENTITIES_PLAYER_H_
