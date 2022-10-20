#include "Robot.h"

void Robot::init(double xPos, double yPos) {
	SDL_Log("Robot::Init");
	this->horizontalPosition = xPos;
	this->verticalPosition = yPos;
	enabled = true;
	RenderComponent* render = (RenderComponent*)components[1];
	if (botType == Message::REDBOT) {
		render->changeSprite("data/redbot.bmp");
	}
	else if (botType == Message::CYANBOT) {
		render->changeSprite("data/cyanbot.bmp");
	}
}

void Robot::receive(Message m) {
	if (!enabled)
		return;

	if (m == Message::HIT) {
		enabled = false;
		components[0]->receive(Message::ROBOT_HIT);
		send(Message::ROBOT_HIT); // re-broadcast the message to signal that the robot has been hit (used to increase the score)
		//SDL_Log("Robot::Hit");
	}
	if (m == Message::NEW_ROOM)
		components[0]->receive(Message::NEW_ROOM);

}

void Robot::receive(Message m, GameObject* go) {
	if (m == Message::PLAYER) {
		playerX = go->horizontalPosition;
		playerY = go->verticalPosition;
	}

	if (m == Message::WALL)
		components[0]->receive(Message::WALL, go);
}