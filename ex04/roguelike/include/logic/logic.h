#pragma once

#include "enviorment_variables.h"
#include <vector>
#include "utils/vec2.h"

class Logic {
	//represents our game in the logic
	//convention 1 = wall 0 = walkable

	int rows;
	int columns;
	bool loadMap(std::string mapFile, int startRow, int startColumn);

public:

	int areaSize;
	std::vector<int> playfield;
	Logic();
	bool load(std::string areaFile);
	bool checkMove(const Vec2& pos,const Vec2& move);
};
