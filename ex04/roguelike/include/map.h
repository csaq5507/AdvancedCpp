#ifndef ROGUELIKE_MAP_H_
#define ROGUELIKE_MAP_H_

#include <SDL.h>
#include <vector>
#include <iostream>
#include <memory>
#include "sprite_set.h"
#include "utils/vec2.h"
#include "tile.h"

class Map {
public:
	std::vector<Tile> tileList;
    std::shared_ptr<SpriteSet> sprideSet;

	Map();

	bool load(std::string filename);
	void render(SDL_Renderer* renderer, Vec2 mapOffset);
};

#endif //ROGUELIKE_MAP_H_