#ifndef ROGUELIKE_RESOURCE_LOADER_H
#define ROGUELIKE_RESOURCE_LOADER_H

#include <map>
#include <memory>
#include <string>

#include <SDL.h>

#include "sprite_set.h"

class ResourceLoader {
  private:
    SDL_Renderer *renderer;

    std::map<std::string, std::shared_ptr<SpriteSet>> loaded_sprite_sets;

  public:
    ResourceLoader(SDL_Renderer *renderer);

    std::shared_ptr<SpriteSet> loadSpriteSet(std::string filename);
};

#endif  // ROGUELIKE_RESOURCE_LOADER_H
