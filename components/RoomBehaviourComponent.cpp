#include "RoomBehaviourComponent.h"

void RoomBehaviourComponent::create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<Wall>* wall_pool) {

	Component::create(system, go, game_objects);
	this->wall_pool = wall_pool;
	this->room = (Room*)go;
	this->timer = 0;
	//CREATE FIXED LAYOUT
	int x = 0;
	int y = 0;
	//horizontal walls
	for (auto i = 0; i < 76; i++) {
		Wall* wall = wall_pool->firstAvailable();
		//upper left walls
		wall->init(x, y);
		game_objects->insert(wall);
		x += 16;
		if (i == 18) {  //upper right walls
			x = 432;
		}
		else if (i == 37) { //lower left walls
			x = 0;
			y = 432;
		}
		else if (i == 56) { //lower right walls
			x = 432;
		}
	}

	//vertical walls
	x = 0;
	y = 16;

	for (auto i = 0; i < 36; i++) {
		Wall* wall = wall_pool->firstAvailable();
		//upper left walls
		wall->init(x, y);
		game_objects->insert(wall);
		y += 16;
		if (i == 8) {  //lower left walls
			y = 288;
		}
		else if (i == 17) { //upper right walls
			x = 720;
			y = 16;
		}
		else if (i == 26) { //lower right walls
			y = 288;
		}
	}

	//Pillars
	x = 144;
	y = 144;
	for (auto i = 0; i < 8; i++) {
		Wall* wall = wall_pool->firstAvailable();
		wall->init(x, y);
		game_objects->insert(wall);
		x += 144;
		if (i == 3) {
			x = 144;
			y = 288;
		}
	}

}

void RoomBehaviourComponent::init() {
	//RANDOM MAZE GENERATOR INIT HERE
	//PRNG, Linear congruential generator
	// X(n+1) = (Xn* 7 + 12627) http://www.drcjt.myzen.co.uk/Berzerk.html
	// random_numer = Xn >> 8
	this->roomX = 0;
	this->roomY = 0;
	//first room
	generateRoom(roomX + roomY);
	closeExit(Message::WEST);
}

void RoomBehaviourComponent::generateRoom(int roomNr) {

	room->send(Message::NEW_ROOM);

	//clear room 64 + 8 in wall pool
	freeWallTiles();
	seed = (roomNr * 7) + 12627;
	int x = 144;
	int y = 144;
	for (auto row = 0; row < 2; row++) {
		for (auto col = 0; col < 4; col++) {
			generateRandomNumber(seed);
			int pillarValue = generateRandomNumber(seed);
			int wallDir = pillarValue & 3;
			drawWall(x, y, wallDir);
			//PILLAR SETTING
			x += 144;
			if (col == 3) {
				x = 144;
			}
		}
		y += 144;
	}
}

void RoomBehaviourComponent::closeExit(Message m) {
	if (m == Message::NORTH) {
		drawWall(304, 0, 2); //draw in dir east
	}
	else if (m == Message::SOUTH) { //draw in dir south
		drawWall(304, 432, 2);
	}
	else if (m == Message::EAST) { //draw in dir east
		drawWall(720, 160, 1);
	}
	else if (m == Message::WEST) { //draw in dir west
		drawWall(0, 160, 1);
	}
}

int RoomBehaviourComponent::generateRandomNumber(int newSeed) {
	seed = (newSeed * 7) + 12627;
	return seed >> 8;
}

void RoomBehaviourComponent::update(float dt) {
	//if player near wall change wall color
	timer += dt;

	if (timer >= 15) {
		room->send(Message::SPAWN_SENTRY);
	}

}

void RoomBehaviourComponent::drawWall(int x, int y, int direction) {
	if (direction == 0) { //NORTH
		for (auto i = 0; i < 9; i++) {
			Wall* wall = wall_pool->firstAvailable();
			wall->init(x, y);
			game_objects->insert(wall);
			y -= 16;
		}
	}

	else if (direction == 1) { //SOUTH
		for (auto i = 0; i < 9; i++) {
			Wall* wall = wall_pool->firstAvailable();
			wall->init(x, y);
			game_objects->insert(wall);
			y += 16;
		}
	}

	else if (direction == 2) { //EAST
		for (auto i = 0; i < 9; i++) {
			Wall* wall = wall_pool->firstAvailable();
			wall->init(x, y);
			game_objects->insert(wall);
			x += 16;
		}
	}
	else if (direction == 3) { //WEST
		for (auto i = 0; i < 9; i++) {
			Wall* wall = wall_pool->firstAvailable();
			wall->init(x, y);
			game_objects->insert(wall);
			x -= 16;
		}
	}
}

void RoomBehaviourComponent::freeWallTiles() {
	for (int i = 112; i < 193; i++) {
		wall_pool->pool[i]->disable();
	}
}

void RoomBehaviourComponent::receive(Message m) {
	if (m == Message::NORTH) {
		if (roomY == 0)
			roomY = 256;
		else
			roomY--;
		generateRoom(roomX + roomY);

		//close lower exit
		closeExit(Message::SOUTH);
	}
	else if (m == Message::SOUTH) {
		if (roomY == 256)
			roomY = 0;
		else
			roomY++;
		generateRoom(roomX + roomY);
		//close upper exit
		closeExit(Message::NORTH);
	}
	else if (m == Message::EAST) {
		if (roomX == 256)
			roomX = 0;
		else
			roomX++;
		generateRoom(roomX + roomY);
		closeExit(Message::WEST);
	}
	else if (m == Message::WEST) {
		if (roomX == 0)
			roomX = 256;
		else
			roomX--;
		generateRoom(roomX + roomY);
		closeExit(Message::EAST);
	}

	room->send(Message::DESPAWN_SENTRY);
	timer = 0.0;
}
