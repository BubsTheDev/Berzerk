#include "Sentry.h"

void Sentry::init(double xPos, double yPos) {
	SDL_Log("Sentry::Init");
	GameObject::init();
	this->horizontalPosition = xPos;
	this->verticalPosition = yPos;
	stop = true;
}

void Sentry::receive(Message m) {
	components[0]->receive(m);

	if ((m == Message::SPAWN_SENTRY || m == Message::LEVEL_WIN) && stop) {
		this->horizontalPosition = startX;
		this->verticalPosition = startY;
		stop = false;
	}

	if (m == Message::DESPAWN_SENTRY && !stop)  {
		this->horizontalPosition = -32.0;
		this->verticalPosition = -32.0;
		stop = true;
	}
}

void Sentry::receive(Message m, GameObject* go) {
	if (m == Message::PLAYER) {
		Player* player = (Player*)go;
		playerX = player->horizontalPosition;
		playerY = player->verticalPosition;
		startX = player->startX;
		startY = player->startY;
	}
}