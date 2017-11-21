#ifndef ROGUELIKE_ENV_H_
#define ROGUELIKE_ENV_H_

constexpr int map_width = 40;  //this means that a map file consists of 40 entries per line
constexpr int map_height = 40; //this means that a map file consists has 40 lines

constexpr int tile_size = 32;  //texture size,this means each tile takes 32*32 pixels from the texture file

constexpr int window_width = 1280;
constexpr int window_height = 960;

enum Direction{north, east, south, west};


#endif //ROGUELIKE_ENV_H_