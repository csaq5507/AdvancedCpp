#pragma once

#include "enviorment_variables.h"
#include <vector>
#include "utils/vec2.h"
#include "Area.h"

class Logic {
	//represents our game in the logic
	int rows;
	int columns;
	void Logic::loadMap(int rowMapIndex, int columnMapIndex, Map& map);

public:

	int areaSize;
	std::vector<int> playfield;
	Logic();
	bool load(Area area);
	bool checkMove(const Vec2& pos,const Vec2& move);
};
