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

    pickable_item(Game &game, Vec2 pos, Item what) : Entity(game, pos, what.getSpriteSet(),10000), item(what) { }

    void update() override {

    }

    void render(SDL_Renderer* renderer, const Vec2& cameraPos){
        SDL_Rect dst;
        //The camera vector points to the lef upper vertex where we start render
        //hence we need to offset the position of the enemys to render them in the correnct pixel coordinates
        dst.x = (this->getPos().x * tile_size) - cameraPos.x;
        dst.y = (this->getPos().y * tile_size) - cameraPos.y;
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
