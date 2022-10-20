#include "BulletBehaviourComponent.h"

void BulletBehaviourComponent::update(float dt) {
	Bullet* bullet = (Bullet*)go;
	switch (bullet->shootDirection) {
	case Message::NORTH:
		bullet->verticalPosition -= BULLET_SPEED* dt; //up
		if (go->verticalPosition < 0)
			go->enabled = false;
		break;
	case Message::SOUTH:
		bullet->verticalPosition -= BULLET_SPEED* -dt; //down
		if (go->verticalPosition > 420)
			go->enabled = false;
		break;
	case Message::WEST:
		bullet->horizontalPosition += -dt* BULLET_SPEED; //left
		if (go->horizontalPosition < 0)
			go->enabled = false;
		break;
	case Message::EAST:
		bullet->horizontalPosition += dt* BULLET_SPEED; //right
		if (go->horizontalPosition > 712)
			go->enabled = false;
		break;
	case Message::NORTHWEST:
		bullet->verticalPosition -= BULLET_SPEED* dt; //up 
		bullet->horizontalPosition += -dt* BULLET_SPEED; // left
		if (go->verticalPosition < 0 || go->horizontalPosition < 0)
		go->enabled = false;
		break;
	case Message::NORTHEAST:
		bullet->verticalPosition -= BULLET_SPEED* dt; //up
		bullet->horizontalPosition += dt* BULLET_SPEED; //right
		if (go->verticalPosition < 0 || go->horizontalPosition > 712)
			go->enabled = false;
		break;
	case Message::SOUTHWEST:
		bullet->verticalPosition -= BULLET_SPEED* -dt; //down
		bullet->horizontalPosition += -dt* BULLET_SPEED; // left
		if (go->verticalPosition > 420 || go->horizontalPosition < 0)
			go->enabled = false;
		break;
	case Message::SOUTHEAST:
		bullet->verticalPosition -= BULLET_SPEED * -dt; //down
		bullet->horizontalPosition += dt* BULLET_SPEED; //right
		if (go->verticalPosition > 420 || go->horizontalPosition > 712)
			go->enabled = false;
		break;
	}

}