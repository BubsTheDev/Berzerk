#include "Wall.h"

void Wall::init(double xPos, double yPos) {
	//SDL_Log("Wall::Init");
	GameObject::init();
	enabled = true;

	horizontalPosition = xPos;
	verticalPosition = yPos;
}

void Wall::disable() {
	enabled = false;
}