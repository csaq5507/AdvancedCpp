#include "resource_loader.h"

#include <cassert>

#include <SDL_image.h>

#include "utils/logging.h"

// -- Base Path (resource folder assumed to be located in CWD)
const std::string RESOURCES_PATH = "resources/";

// -- Resource Group Specific Paths
const std::string SPRITE_SETS_PATH = RESOURCES_PATH + "sprites/";

// -- Special Resources
const std::string ERROR_SPRITE_SET_FILENAME = "error.png";

ResourceLoader::ResourceLoader(SDL_Renderer *renderer) : renderer(renderer) {
    assert(renderer);

    // fallback error sprite set
    loadSpriteSet(ERROR_SPRITE_SET_FILENAME);
}

std::shared_ptr<SpriteSet> ResourceLoader::loadSpriteSet(std::string filename) {
    // already loaded?
    {
        auto it = loaded_sprite_sets.find(filename);
        if (it != loaded_sprite_sets.end()) {
            return it->second;
        }
    }

    auto filepath = SPRITE_SETS_PATH + filename;
    SDL_Surface *surface = IMG_Load(filepath.c_str());
    if (!surface) {
        ERROR("Could not load SpriteSet from '%s'.", filepath.c_str());

        // fallback
        auto it = loaded_sprite_sets.find(ERROR_SPRITE_SET_FILENAME);
        if (it == loaded_sprite_sets.end()) {
            FATAL("Could not even load error SpriteSet.");
        }
        return it->second;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        FATAL("Could not create texture from '%s' surface.", filepath.c_str());
    }

    SDL_FreeSurface(surface);

    INFO("Loaded SpriteSet from '%s'.", filepath.c_str());

    auto it = loaded_sprite_sets
                  .emplace(filename, std::make_shared<SpriteSet>(texture))
                  .first;
    return it->second;
}
