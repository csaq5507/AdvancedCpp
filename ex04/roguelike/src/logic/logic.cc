#include "logic/logic.h"
#include <fstream>
#include <algorithm>
#include "tile.h"
#include <sstream>
#include <iostream>
Logic::Logic() {}

bool Logic::load(std::string filename) {
	playfield.clear();
	filename="resources/maps/"+filename;
	auto stream = std::ifstream(filename);

	std::string line;
	//drop sprite file name
	std::getline(stream, line);

	std::getline(stream, line);
	//extract areaSize
	areaSize = std::stoi(line);
	//compute the size
	rows = map_height * areaSize;
	columns = map_width * areaSize;
	playfield.resize(rows * columns,0);
	for (int y = 0; y < areaSize; y++) {
		std::getline(stream, line);
		std::stringstream ss(line);
		for (int x = 0; x < areaSize; x++) {
			std::getline(ss, line, ' ');
			loadMap(line, y, x);
		}
	}
	return true;
}

//TODO test
bool Logic::loadMap(std::string filename, int rowMapIndex, int columnMapIndex) {
	filename="resources/maps/"+filename;
	auto stream = std::ifstream(filename);

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
				playfield[currentRow + currentCol] = 1;
			}
		}
	}
	return true;
}
	//TODO test
bool Logic::checkMove(const Vec2& pos,const Vec2& move){
	Vec2 tmp = pos + move;
	if(tmp.x < 0 || tmp.y < 0 || tmp.x >= columns || tmp.y >= rows) return false;
	//TODO use enum
	if(playfield[tmp.y * map_width * areaSize + tmp.x] == 1) return false;
	return true;
}
