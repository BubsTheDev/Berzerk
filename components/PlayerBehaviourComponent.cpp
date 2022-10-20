#include "PlayerBehaviourComponent.h"

void PlayerBehaviourComponent::create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<Bullet>* bullet_pool) {
	Component::create(system, go, game_objects);
	this->bullet_pool = bullet_pool;
}

void PlayerBehaviourComponent::init()
{
	go->horizontalPosition = 20;
	go->verticalPosition = 214;

	time_fire_pressed = -10000.f;
}

void PlayerBehaviourComponent::update(float dt)
{
	AvancezLib::KeyStatus keys;
	system->getKeyStatus(keys);
	move(dt, keys);
	if (keys.up || keys.down || keys.left || keys.right)
	{
		if (canFire())
		{
			// fetches a rocket from the pool and use it in game_objects
			Bullet* bullet = bullet_pool->firstAvailable();
			if (bullet != NULL)	// rocket is NULL is the object pool can not provide an object
			{
				bullet->init(go->horizontalPosition, go->verticalPosition);
				if (keys.up && keys.left) {
					bullet->shootDirection = Message::NORTHWEST;
					bullet->verticalPosition -= 16;
					bullet->horizontalPosition -= 16;
				}
				else if (keys.up && keys.right) {
					bullet->shootDirection = Message::NORTHEAST;
					bullet->verticalPosition -= 16;
					bullet->horizontalPosition += 16;
				}
				else if (keys.down && keys.left) {
					bullet->shootDirection = Message::SOUTHWEST;
					bullet->verticalPosition += 16;
					bullet->horizontalPosition -= 16;
				}
				else if (keys.down && keys.right) {
					bullet->shootDirection = Message::SOUTHEAST;
					bullet->verticalPosition += 16;
					bullet->horizontalPosition += 16;
				}
				else if (keys.up) {
					bullet->shootDirection = Message::NORTH;
					bullet->verticalPosition -= 16;
				}
				else if (keys.down) {
					bullet->shootDirection = Message::SOUTH;
					bullet->verticalPosition += 16;
				}
				else if (keys.left) {
					bullet->shootDirection = Message::WEST;
					bullet->horizontalPosition -= 16;
				}
				else if (keys.right) {
					bullet->shootDirection = Message::EAST;
					bullet->horizontalPosition += 16;
				}
				
				game_objects->insert(bullet);
			}
		}
	}

	go->send(Message::PLAYER, go); //send position to robot&sentry
	checkNewLevel();
}

void PlayerBehaviourComponent::checkNewLevel() {
	//next room detection
	//upper exit
	Player* player = (Player*)go;
	if ((go->verticalPosition > 0 && go->verticalPosition < 8)
		&& (go->horizontalPosition > 304 && go->horizontalPosition < 432)) {
		go->send(Message::NORTH);
		//go->horizontalPosition = 360;
		go->verticalPosition = 400;
		player->startX = go->horizontalPosition;
		player->startY = 400;
	}
	//lower exit
	if ((go->verticalPosition > 420 && go->verticalPosition < 428)
		&& (go->horizontalPosition > 304 && go->horizontalPosition < 432)) {
		go->send(Message::SOUTH);
		go->verticalPosition = 20;
		//go->horizontalPosition = 360;
		player->startX = go->horizontalPosition;
		player->startY = 20;
	}
	//left exit
	if ((go->verticalPosition > 160 && go->verticalPosition < 288)
		&& (go->horizontalPosition > 0 && go->horizontalPosition < 8)) {
		go->send(Message::WEST);

		go->horizontalPosition = 700;
		//go->verticalPosition = 214;

		player->startX = 700;
		player->startY = go->verticalPosition;
	}
	//right exit
	if ((go->verticalPosition > 160 && go->verticalPosition < 288)
		&& (go->horizontalPosition > 712 && go->horizontalPosition < 730)) {
		go->send(Message::EAST);
		go->horizontalPosition = 20;
		//go->verticalPosition = 214;
		player->startX = 20;
		player->startY = go->verticalPosition;
	}
}

// move the player left or right
// param move depends on the time, so the player moves always at the same speed on any computer
void PlayerBehaviourComponent::move(float move, AvancezLib::KeyStatus keys)
{
	if (keys.w && keys.d) { //NE
		go->verticalPosition -= PLAYER_SPEED* move;
		go->horizontalPosition += move* PLAYER_SPEED;
	}
	else if (keys.w && keys.a) { //NW
		go->verticalPosition -= PLAYER_SPEED* move;
		go->horizontalPosition += -move* PLAYER_SPEED;
	}
	else if (keys.s && keys.d) { //SE
		go->verticalPosition -= PLAYER_SPEED* -move;
		go->horizontalPosition += move* PLAYER_SPEED;
	}
	else if (keys.s && keys.a) { //SW
		go->verticalPosition -= PLAYER_SPEED* -move;
		go->horizontalPosition += -move* PLAYER_SPEED;
	}
	else if (keys.d) { //W
		go->horizontalPosition += move* PLAYER_SPEED;
	}
	else if (keys.a) { //E
		go->horizontalPosition += -move* PLAYER_SPEED;
	}
	else if (keys.s) { //S
		go->verticalPosition -= PLAYER_SPEED* -move;
	}
	else if (keys.w) { //N
		go->verticalPosition -= PLAYER_SPEED* move;
	}

	//window boundary check (mainly for enabled godmode)
	if (go->horizontalPosition > 736-18)
		go->horizontalPosition = 736-18;

	if (go->horizontalPosition < 5)
		go->horizontalPosition = 5;

	if (go->verticalPosition > 448-26)
		go->verticalPosition = 448-26;

	if (go->verticalPosition < 5)
		go->verticalPosition = 5;
}

// return true if enough time has passed from the previous rocket
bool PlayerBehaviourComponent::canFire()
{
	// shoot just if enough time passed by
	if ((system->getElapsedTime() - time_fire_pressed) < (FIRE_TIME_INTERVAL / game_speed))
		return false;

	time_fire_pressed = system->getElapsedTime();

	return true;
}

void PlayerBehaviourComponent::receive(Message m) {
	if (m == Message::HIT) {
		//new random level
		//set position to start position
		//sleep for 1 second
		go->send(Message::EAST);
		init();
		SDL_Delay(1000);
	}
	if (m == Message::NEW_ROOM) {
		for (int i = 0; i < bullet_pool->pool.size(); i++) {
			bullet_pool->pool[i]->enabled = false;
		}
	}
}
