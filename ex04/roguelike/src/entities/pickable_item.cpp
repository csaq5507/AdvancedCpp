//
// Created by ivan on 15/12/17.
//

#include "entities/pickable_items.h"
template <class Item>
void pickable_item<Item>::update() {

}

template <class Item>
void pickable_item<Item>::render(SDL_Renderer* renderer, const Vec2& cameraPos){
    SDL_Rect dst;
    dst.x = window_width / 2;
    dst.y = window_height/2;

    dst.w = tile_size;
    dst.h = tile_size;
    auto sprite_set = this->getSpriteSet();
    SDL_RenderCopy(renderer, sprite_set->getTexture(),
                   sprite_set->getRect(), &dst);
}

template <class Item>
void pickable_item<Item>::serialize(std::fstream& f) {
}

template <class Item>
pickable_item<Item> pickable_item<Item>::deserialize(std::fstream& f, Game& game) {
    return nullptr;
}