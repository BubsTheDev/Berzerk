#pragma once

#include "../Component.h"
#include "../ObjectPool.h"
#include "../objects/Wall.h"
#include "../objects/Sentry.h"
#include "../objects/Room.h"

class RoomBehaviourComponent : public Component {

public:
	virtual void create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<Wall>* wall_pool);

	virtual void init();

	virtual void update(float dt);

	virtual void receive(Message m);

private:
	void generateRoom(int roomNr);

	void closeExit(Message m);

	int generateRandomNumber(int newSeed);

	void drawWall(int x, int y, int direction);

	void freeWallTiles();

	Room* room;
	float timer;
	ObjectPool<Wall>* wall_pool;
	int seed;
	int roomX;
	int roomY;
};