#include "RobotBehaviourComponent.h"
#include <iostream>

void RobotBehaviourComponent::create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<Bullet>* bullets_pool, ParticlePool* particle_pool) {
	Component::create(system, go, game_objects);
	this->bullets_pool = bullets_pool;
	this->robot = (Robot*)go;
	this->particle_pool = particle_pool;
}

void RobotBehaviourComponent::update(float dt) {
	//move towards player

	setTrackStage();

	checkRobotPosition();

	if (trackState == Message::TRACK_Y) {
		if (robot->playerY < robot->verticalPosition) { // player above robot
			robot->verticalPosition -= ROBOT_SPEED * dt;
		}
		if (robot->playerY > robot->verticalPosition) { //player below robot
			robot->verticalPosition -= ROBOT_SPEED * -dt;
		}
	}
	else if (trackState == Message::TRACK_X) {
		if (robot->playerX < robot->horizontalPosition) { //player left of robot
			robot->horizontalPosition += ROBOT_SPEED * -dt;
		}
		if (robot->playerX >= robot->horizontalPosition) { //player right of robot
			robot->horizontalPosition += ROBOT_SPEED * dt;
		}
	}
}

void RobotBehaviourComponent::checkRobotPosition() {
	double deltaX = robot->playerX - robot->horizontalPosition;
	double deltaY = robot->playerY - robot->verticalPosition;
	double delta = std::abs(deltaX) - std::abs(deltaY);

	if (robot->playerY < robot->verticalPosition) { //player is north
		if ((deltaX < 0 && deltaY < 0) && (delta > -5 && delta < 5)) {
			fire(Message::NORTHWEST, -16, -16);
		}
		else if ((deltaX > 0 && deltaY < 0) && (delta > -5 && delta < 5)) {
			fire(Message::NORTHEAST, 16, -16);
		}
		else if (robot->horizontalPosition <= robot->playerX + 16 && robot->horizontalPosition >= robot->playerX - 16) { // player is north in between shooting area
			fire(Message::NORTH, 0, -16);
		}

	}
	if (robot->playerY > robot->verticalPosition) { //player is south
		if ((deltaX > 0 && deltaY > 0) && (delta > -5 && delta < 5)) {
			fire(Message::SOUTHEAST, 16, 16);
		}
		else if ((deltaX < 0 && deltaY > 0) && (delta > -5 && delta < 5)) {
			fire(Message::SOUTHWEST, -16, 16);
		}
		else if (robot->horizontalPosition <= robot->playerX + 16 && robot->horizontalPosition >= robot->playerX - 16) { // player is south in between shooting area
			fire(Message::SOUTH, 0, 16);
		}

	}
	if (robot->playerX < robot->horizontalPosition) {
		if (robot->verticalPosition <= robot->playerY + 16 && robot->verticalPosition >= robot->playerY - 16) { // player is west in between shooting area
			fire(Message::WEST, -16, 0);
		}

	}
	if (robot->playerX >= robot->horizontalPosition) {
		if (robot->verticalPosition <= robot->playerY + 16 && robot->verticalPosition >= robot->playerY - 16) { // player is east in between shooting area
			fire(Message::EAST, 16, 0);
		}

	}
}

void RobotBehaviourComponent::fire(Message direction, int x, int y) {
	if (canFire()) {
		Bullet* bullet = bullets_pool->firstAvailable();
		if (bullet != NULL) {
			bullet->init(robot->horizontalPosition + x, robot->verticalPosition + y);
			bullet->shootDirection = direction;
			game_objects->insert(bullet);
		}
	}
}

bool RobotBehaviourComponent::canFire() {
	// shoot just if enough time passed by
	if ((system->getElapsedTime() - time_bullet_launched) < (BULLET_TIME_INTERVAL / game_speed))
		return false;

	if (robot->botType == Message::REDBOT) {
		if (bullets_pool->countEnabled() >= 1)
			return false;
	}
	else if (robot->botType == Message::CYANBOT) {
		if (bullets_pool->countEnabled() >= 2)
			return false;
	}
	else if (robot->botType == Message::YELLOWBOT) {
		return false;
	}

	time_bullet_launched = system->getElapsedTime();

	return true;
}

void RobotBehaviourComponent::setTrackStage() {
	srand(time(NULL));
	int random = rand() % 2;

	if (random == 0)
		trackState = Message::TRACK_X;
	else
		trackState = Message::TRACK_Y;
}

void RobotBehaviourComponent::receive(Message m) {
	if (m == Message::NEW_ROOM) {
		for (int i = 0; i < bullets_pool->pool.size(); i++) {
			bullets_pool->pool[i]->enabled = false;
		}
	}

	if (m == Message::ROBOT_HIT) {
		particle_pool->create(robot->horizontalPosition, robot->verticalPosition, 40, 40, 80);
	}
}

void RobotBehaviourComponent::receive(Message m, GameObject* go) {
	if (m == Message::WALL) {
		if (go->verticalPosition < robot->verticalPosition) { //wall above robot
			robot->verticalPosition += 1;
		}
		else if (go->verticalPosition > robot->verticalPosition) { //wall under robot
			robot->verticalPosition -= 1;
		}
		if (go->horizontalPosition > robot->horizontalPosition) { //wall right
			robot->horizontalPosition -= 1;
		}
		else if (go->horizontalPosition < robot->horizontalPosition) { //wall left
			robot->horizontalPosition += 1;
		}
	}

}