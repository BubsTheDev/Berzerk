#include "Bullet.h"

void Bullet::init(double xPos, double yPos) {
	SDL_Log("Bullet::Init");
	GameObject::init();
	shootDirection = Message::NO_MSG;
	horizontalPosition = xPos;
	verticalPosition = yPos;
}

void Bullet::receive(Message m) {
	if (!enabled)
		return;

	if (m == Message::HIT)
	{
		enabled = false;
	}
}
