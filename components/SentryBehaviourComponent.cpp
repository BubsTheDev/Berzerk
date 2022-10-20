#include "SentryBehaviourComponent.h"

void SentryBehaviourComponent::create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects) {
	Component::create(system, go, game_objects);
}

void SentryBehaviourComponent::update(float dt) {
	Sentry* sentry = (Sentry*)go;
	int amplitude = 75;
	//move towards player
	//object.pos.x = object.speed* getElapsedTime();
	//object.pos.y = sin(object.speed* getElapsedTime())* amplitude;
	if (!sentry->stop) {
		if (sentry->playerY < sentry->verticalPosition) { // player above robot
			sentry->verticalPosition -= SENTRY_SPEED * dt; //move up
		}
		if (sentry->playerY > sentry->verticalPosition) { //player below robot
			sentry->verticalPosition -= SENTRY_SPEED * -dt; //move down
		}
		if (sentry->playerX < sentry->horizontalPosition) { //player left of robot
			sentry->horizontalPosition += SENTRY_SPEED / 2 * -dt; //move right
		}
		if (sentry->playerX >= sentry->horizontalPosition) { //player right of robot
			sentry->horizontalPosition += SENTRY_SPEED / 2 * dt; //move left
		}
	}
}

void SentryBehaviourComponent::receive(Message m) {
	if (m == Message::LEVEL_WIN) {
		if (SENTRY_SPEED < PLAYER_SPEED)
			SENTRY_SPEED *= 2;
	}
	if (m == Message::SPAWN_SENTRY) {
		if (SENTRY_SPEED >= PLAYER_SPEED)
			SENTRY_SPEED /= 2;
	}
}