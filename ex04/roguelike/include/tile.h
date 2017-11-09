#ifndef ROGUELIKE_TILE_H_
#define ROGUELIKE_TILE_H_


#include "enviorment_variables.h"

enum TileType {
	TILE_TYPE_NONE = 0, //indicates that the tile should not be rendered
	TILE_TYPE_NORMAL = 1,	//indicates walkable path
	TILE_TYPE_BLOCK = 2,	//indicates not walkable path, needed if the collision will be computed with the tiles
};

class Tile {
public:
	int tile_id;		  //identifies which texture is attached to this tile
	TileType tile_type;

	Tile();
};

#endif //ROGUELIKE_TILE_H_