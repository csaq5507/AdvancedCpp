#pragma once
#include <SDL.h>
#include <vector>
#include <iostream>
#include <memory>
#include "sprite_set.h"
#include "utils\vec2.h"
#include "Tile.h"

class Map {
public:
	std::shared_ptr<SpriteSet> sprideSet;

private:
	std::vector<Tile> tileList;
public:
	Map();

	bool load(std::string filename);
	void render(SDL_Renderer* renderer, Vec2 mapOffset);
};