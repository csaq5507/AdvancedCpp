#pragma once
#include <memory>
#include "Map.h"
#include "resource_loader.h"

class Area {
public:
	std::vector<Map> mapList;
	std::shared_ptr<SpriteSet> spride;
private:
	int areaSize;


public:
	Area::Area();
	bool load(ResourceLoader& resourceLoader, std::string filename);
	void render(SDL_Renderer* rendere, Vec2 cameraPos);

};