#ifndef ROGUELIKE_SPRITE_SET_H_
#define ROGUELIKE_SPRITE_SET_H_

#include <SDL.h>

const int SPRITE_SIZE = 32;

class SpriteSet {
  private:
    SDL_Texture *texture;

    SDL_Rect *rect = nullptr;

  public:
    SpriteSet(SDL_Texture *texture);

    SpriteSet(const SpriteSet &) = delete;
    SpriteSet &operator=(const SpriteSet &) = delete;

    SpriteSet(SpriteSet &&) = delete;
    SpriteSet &operator=(SpriteSet &&) = delete;

    ~SpriteSet();

    void setRect(int x, int y, int w, int h);

    void clearRect();

    SDL_Texture *getTexture() {
        return texture;
    }

    SDL_Rect *getRect() {
        return rect;
    }
};

#endif  // ROGUELIKE_SPRITE_SET_H_
