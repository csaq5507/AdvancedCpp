#include "logic/logic.h"
#include <fstream>
#include <algorithm>
#include "tile.h"
#include <sstream>
#include <iostream>

Logic::Logic() {}

void Logic::loadMap(int rowMapIndex, int columnMapIndex, Map& map) {
	for (int y = 0; y < map_height; y++) {
		for (int x = 0; x < map_width; x++) {
			//compute offstets of map to 1d array
			int currentCol = columnMapIndex * map_width + x;
			int currentRow = rowMapIndex  * map_height * map_width * areaSize + y * map_width * areaSize;
			auto& currentTile = map.tileList[y * map_width + x];
			//laod tile property
			playfield[currentRow + currentCol] = currentTile.tile_type;
		}
	}
}

bool Logic::load(Area area) {
	playfield.clear();
	areaSize = area.GetAreaSize();
	rows = map_height * areaSize;
	columns = map_width * areaSize;
	playfield.resize(rows * columns, 0);
	for (int x = 0; x < areaSize; x++) {
		for (int y = 0; y < areaSize; y++) {
			auto& currentMap = area.mapList[x * areaSize + y];
			loadMap(x, y, currentMap);
		}
	}
	return false;
}

bool Logic::checkMove(const Vec2& pos,const Vec2& move){
	Vec2 tmp = pos + move;
	if(tmp.x < 0 || tmp.y < 0 || tmp.x >= columns || tmp.y >= rows) return false;
	if(playfield[tmp.y * map_width * areaSize + tmp.x] == TILE_TYPE_BLOCK) return false;
	return true;
}