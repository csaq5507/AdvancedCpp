#include "sprite_set.h"

#include <cassert>

SpriteSet::SpriteSet(SDL_Texture *texture) : texture(texture) {
    assert(texture);
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

void SpriteSet::clearRect() {
    if (rect) {
        delete rect;
        rect = nullptr;
    }
}
