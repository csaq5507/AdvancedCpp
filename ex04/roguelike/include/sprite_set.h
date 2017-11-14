#ifndef ROGUELIKE_SPRITE_SET_H_
#define ROGUELIKE_SPRITE_SET_H_

#include <SDL.h>
#include <vector>
#include "enviorment_variables.h"

class SpriteSet {
  private:
    SDL_Texture *texture;

    SDL_Rect *rect = nullptr;

    std::vector<int> direction_map;

  public:
    SpriteSet(SDL_Texture *texture);

    SpriteSet(const SpriteSet &) = delete;
    SpriteSet &operator=(const SpriteSet &) = delete;

    SpriteSet(SpriteSet &&) = delete;
    SpriteSet &operator=(SpriteSet &&) = delete;

    ~SpriteSet();

    void set_texture_map(std::vector<int> texture_map);

    void setRect(int x, int y, int w, int h);

    void update_texture(Direction direction);

    void clearRect();

    SDL_Texture *getTexture() {
        return texture;
    }

    SDL_Rect *getRect() {
        return rect;
    }
};

#endif  // ROGUELIKE_SPRITE_SET_H_
