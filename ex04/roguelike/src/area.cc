#include "area.h"
#include "enviorment_variables.h"
#include <algorithm>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


Area::Area() {
	areaSize = 0;  //stored in the area file, always considered square
}

bool Area::load(ResourceLoader& resourceLoader, std::string filename) {
	mapList.clear();
    filename="resources/maps/"+filename;
	auto stream = std::ifstream(filename, std::ifstream::in);
	std::string line;
	std::getline(stream, line);

	spride = resourceLoader.loadSpriteSet(line);
	if (!spride) return false;

	std::getline(stream, line);

	areaSize = std::stoi(line);
	for (int y = 0; y < areaSize; y++) {
		for (int x = 0; x < areaSize; x++) {
			std::getline(stream, line,' ');
			int idx = line.find('\n');
			if(idx!=-1)
			line.erase(idx, line.length() - idx);
			Map map;
			if (map.load(line) == false) return false;
			map.sprideSet = spride;
			mapList.push_back(map);
		}
	}

	return true;
}

void Area::render(SDL_Renderer* renderer, Vec2 cameraPos) {
	//compute pixel coordinates from maps
	Vec2 mapPixelCoordinate;
	int mapWidthPxCoord = map_width * tile_size;
	int mapHeightPxCoord = map_height * tile_size;

	//compute the column
	int firstMapId = cameraPos.x / mapWidthPxCoord;
	//compute the row
	firstMapId += ((cameraPos.y / mapHeightPxCoord) * areaSize);

	//in our case i is < 4 because in the current resolution we will maximally render 4 maps
	for (int i = 0; i < 4; i++) {
		int mapId = firstMapId + ((i / 2) * areaSize) + (i % 2);
		if (mapId < 0 || mapId >= mapList.size()) continue;
		//compute map offset in pixel coordinates
		Vec2 mapPixelCoordOffset;
		mapPixelCoordOffset.x = ((mapId % areaSize) * mapWidthPxCoord) - cameraPos.x;
		mapPixelCoordOffset.y = ((mapId / areaSize) * mapHeightPxCoord) - cameraPos.y;
		mapList[mapId].render(renderer, mapPixelCoordOffset);
	}
}