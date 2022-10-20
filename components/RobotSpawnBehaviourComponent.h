#pragma once

#include "../Component.h"
#include "../objects/Robot.h"
#include "../objects/Bullet.h"
#include <ctime>

class RobotSpawnBehaviourComponent : public Component {
	float time_bomb_launched;
	SDL_Rect top1, top2, top3, top4, mid1, mid2, mid3, low1, low2, low3, low4;
	ObjectPool<Robot>* robots_pool;
	ObjectPool<Bullet>* bullets_pool;
	std::vector<SDL_Rect> rectangles;


public:
	virtual ~RobotSpawnBehaviourComponent();

	virtual void create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, 
		ObjectPool<Robot>* robots_pool, ObjectPool<Bullet>* bullets_pool);

	virtual void init();

	virtual void update(float dt);

	virtual void receive(Message m);

private:
	void spawnRobots();

	Message checkBotType();

	void clearRobots();

	void setNumberOfRobots();

	SDL_Rect getNewRobotPosition(SDL_Rect spawnZone, SDL_Rect existingRobot);

	SDL_Rect getRandomRectangle();

	void addZonesToVector();

	bool checkBonus();

	int no_of_robots;
};