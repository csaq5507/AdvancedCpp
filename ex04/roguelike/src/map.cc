#include <fstream>
#include "map.h"
#include "utils/logging.h"

Map::Map() {};

bool Map::load(std::string filename) {
	tileList.clear();
    filename="resources/maps/"+filename;
	auto stream = std::ifstream(filename);
	
	int id;
	char seperator;
	int type;
	//storing each tile in the list beginning with top leftmost tile
	//the tileList represents the map
	for (int y = 0; y < map_height; y++) {
		for (int x = 0; x < map_width; x++) {
			//TODO fix map parser, it BUGGS!!!
			Tile genTile{};
			stream >> id;			//read the id
			stream >> seperator;	//read the seperator ":"
			if (seperator != ':') {
				FATAL("Format error\n");
			}
			stream >> type;			//read the type (block or normal)
			if (id < 0) {
				FATAL("Parse error at file %s\n", filename.c_str());
			}
			genTile.tile_id = id;
			genTile.tile_type = TileType(type);
			tileList.push_back(genTile);
		}
	}
	return true;
}

/*
	mapOffset: stores the pixel offset of the map
*/
void Map::render(SDL_Renderer* renderer, Vec2 mapOffset) {
	if (!sprideSet) return;
	SDL_Texture* tex = sprideSet->getTexture();

	int w, h;
	if (0 != SDL_QueryTexture(tex, NULL, NULL, &w, &h)) {
		FATAL("Could not get Texture information %s", SDL_GetError());
	}

	int TileTextWidth = w / tile_size;  //converting the pixel coordinates to tile coordinates
	int TileTextHeight = h / tile_size; //converting the pixel coordinates to tile coordinates (e.g. if a tile has 32*32 px and the texture contains 64*64 then we have 2 rows of tiles)

	int tileToRenderId = 0;

	for (int y = 0; y < map_height; y++) {
		for (int x = 0; x < map_width; x++) {
			if (tileList[tileToRenderId].tile_type == TILE_TYPE_NONE) {
				tileToRenderId++;
				continue;
			}

			int TilesetX = (tileList[tileToRenderId].tile_id % TileTextWidth) * tile_size;
			int TilesetY = (tileList[tileToRenderId].tile_id / TileTextHeight) * tile_size;
	
			SDL_Rect DestR;

			DestR.x = mapOffset.x + (x * tile_size);
			DestR.y = mapOffset.y + (y * tile_size);
			DestR.w = tile_size;
			DestR.h = tile_size;

			SDL_Rect SrcR;
			SrcR.x = TilesetX;
			SrcR.y = TilesetY;
			SrcR.w = tile_size;
			SrcR.h = tile_size;

			SDL_RenderCopy(renderer, tex, &SrcR, &DestR);

			tileToRenderId++;
		}
	}
}