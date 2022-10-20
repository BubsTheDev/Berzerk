#include "RobotSpawn.h"

RobotSpawn::~RobotSpawn() { SDL_Log("RobotSpawn::~RobotSpawn"); }

void RobotSpawn::init()
{
	SDL_Log("RobotSpawn::Init");
	GameObject::init();
}

void RobotSpawn::receive(Message m) {
	components[0]->receive(m);
}