#include "camera.h"

Camera Camera::CameraControl;

Camera::Camera() {}

void Camera::move(Vec2 m) {
	this->position += m;
}

Vec2 Camera::GetPos() {

	if (entity) {
		Vec2 res = entity->getPixelCoordinate();
		if (mode == TARGET_MODE_CENTER) {
			//Rework this, problem is that the player object has its own possitioning system and we need to convert this to pixel coordinates
			res.x = res.x - (window_width / 2);
			res.y = res.y - (window_height / 2);
		}
		return res;
	}
	return position;
}

void Camera::SetPos(Vec2 p) {
	position.x = p.x;
	position.y = p.y;
}

void Camera::SetTarget(std::shared_ptr<Entity> e) {
	entity = e;
}