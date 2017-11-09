#pragma once

#include "enviorment_variables.h"
#include <vector>
#include "utils/vec2.h"

class Logic {
	//represents our game in the logic
	//convention 1 = wall 0 = walkable
	std::vector<int> playfield;
	int areaSize;
	bool loadMap(std::string mapFile, int startRow, int startColumn);
public:
	Logic();
	bool load(std::string areaFile);
	bool checkMove(Vec2 pos, Vec2 move);
};
