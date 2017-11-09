#ifndef ROGUELIKE_AREA_H_
#define ROGUELIKE_AREA_H_
#include <memory>
#include "map.h"
#include "resource_loader.h"

class Area {
public:
	std::vector<Map> mapList;
	std::shared_ptr<SpriteSet> spride;
private:
	int areaSize;


public:
	Area();
	bool load(ResourceLoader& resourceLoader, std::string filename);
	void render(SDL_Renderer* rendere, Vec2 cameraPos);

};

#endif //ROGUELIKE_AREA_H_