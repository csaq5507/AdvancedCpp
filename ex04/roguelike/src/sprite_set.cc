#include <iostream>
#include "sprite_set.h"
#include <cassert>

SpriteSet::SpriteSet(SDL_Texture *texture) : texture(texture) {
    assert(texture);
    this->direction_map={0,1,2,3};
}

SpriteSet::~SpriteSet() {
    clearRect();
    SDL_DestroyTexture(texture);
}

void SpriteSet::setRect(int x, int y, int w, int h) {
    if (!rect) {
        rect = new SDL_Rect;
    }

    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
}

void SpriteSet::update_texture(Direction direction) {
    this->setRect(0,direction_map[direction]*tile_size,tile_size,tile_size);
}


void SpriteSet::clearRect() {
    if (rect) {
        delete rect;
        rect = nullptr;
    }
}

void SpriteSet::set_texture_map(std::vector<int> texture_map) {
    this->direction_map=texture_map;
}