#include "logic/logic.h"
#include <fstream>
#include <algorithm>
#include "Tile.h"
Logic::Logic() {}

bool Logic::load(std::string areaName) {
	playfield.clear();
	auto stream = std::ifstream(areaName);

	std::string line;
	//drop sprite file name
	std::getline(stream, line);

	std::getline(stream, line);
	//extract areaSize
	areaSize = std::stoi(line);
	//compute the size
	int rows = map_height * areaSize;
	int columns = map_width * areaSize;
	playfield.resize(rows * columns,0);
	for (int y = 0; y < areaSize; y++) {
		for (int x = 0; x < areaSize; x++) {
			std::getline(stream, line, ' ');
			line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
			loadMap(line, y, x);
		}
	}
	return true;
}

//TODO test
bool Logic::loadMap(std::string mapFile, int rowMapIndex, int columnMapIndex) {
	auto stream = std::ifstream(mapFile);

	int id;
	char seperator;
	int type;
	//storing each tile in the list beginning with top leftmost tile
	//the tileList represents the map
	for (int y = 0; y < map_height; y++) {
		for (int x = 0; x < map_width; x++) {
			stream >> id;			//read the id
			stream >> seperator;	//read the seperator ":"
			stream >> type;			//read the type (block or normal)

			if (type == TILE_TYPE_BLOCK) {
				//TODO use enum for understanding
				int currentCol = columnMapIndex * map_width + x;
				int currentRow = rowMapIndex  * map_height * map_width * areaSize + y * map_width * areaSize;
				playfield[rowMapIndex + columnMapIndex] = 1;
			}
		}
	}
	return true;
}
	//TODO test
	bool checkMove(Vec2 pos, Vec2 move){
		Vec2 tmp = pos + move;
		if(tmp.x < 0 || tmp.y < 0 || tmp.x >= playfield.size() || tmp.y >= playfield.size()) return false;
		//TODO use enum
		if(playfield[tmp.y * map_width * areaSize + tmp.x] == 1) return false;
		return true;
	}
