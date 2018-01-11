//
// Created by ivan on 15/12/17.
//

#ifndef ADVANCEDCPP_PICKABLE_ITEMS_H
#define ADVANCEDCPP_PICKABLE_ITEMS_H

#include "entity.h"

template <class Item>
class pickable_item : public Entity {

public:
    Item item;

    pickable_item(Game &game, Vec2 pos, Item what) : Entity(game, pos, what.sprite_set()), item(what) { }

    void update() override;

    void render(SDL_Renderer* renderer, const Vec2& cameraPos);

    void damage(int hp) override;

    void serialize(std::fstream& f);
    static pickable_item deserialize(std::fstream& f, Game& game);
};
#endif //ADVANCEDCPP_PICKABLE_ITEMS_H
