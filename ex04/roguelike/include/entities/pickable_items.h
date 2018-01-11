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

    pickable_item(Game &game, Vec2 pos, Item what) : Entity(game, pos, what.getSpriteSet()), item(what) { }

    void update() override {

    }

    void render(SDL_Renderer* renderer, const Vec2& cameraPos){
        SDL_Rect dst;
        dst.x = window_width / 2;
        dst.y = window_height/2;

        dst.w = tile_size;
        dst.h = tile_size;
        auto sprite_set = this->getSpriteSet();
        SDL_RenderCopy(renderer, sprite_set->getTexture(),
                       sprite_set->getRect(), &dst);
    }

    void serialize(std::fstream& f) {
    }
    static pickable_item deserialize(std::fstream& f, Game& game){
        return nullptr;
    }
};
#endif //ADVANCEDCPP_PICKABLE_ITEMS_H
