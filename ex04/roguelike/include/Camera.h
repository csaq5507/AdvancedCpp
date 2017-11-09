#pragma once
#include <SDL.h>
#include <memory>
#include "enviorment_variables.h"
#include "utils\vec2.h"
#include "entity.h"
enum Camera_Mode {
	TARGET_MODE_NORMAL = 0,
	TARGET_MODE_CENTER
};

class Camera {
public:
	static Camera CameraControl;

private:
	Vec2 position;
	//for centered mode
	std::shared_ptr<Entity> entity;

public:
	Camera_Mode mode;
	Camera();
	void move(Vec2 v);
	Vec2 GetPos();
	void SetPos(Vec2 pos);
	void SetTarget(std::shared_ptr<Entity> entity);
};