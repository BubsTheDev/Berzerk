#include "RobotSpawnBehaviourComponent.h"

RobotSpawnBehaviourComponent::~RobotSpawnBehaviourComponent() {}

void RobotSpawnBehaviourComponent::create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<Robot>* robots_pool, ObjectPool<Bullet>* robotbullets_pool) {
	Component::create(system, go, game_objects);

	this->robots_pool = robots_pool;
	this->bullets_pool = robotbullets_pool;
}

void RobotSpawnBehaviourComponent::init() {
	//Set 11 spawn quadrates, inside those the robots can spawn
	top1 = { 24, 24, 92, 88 }; // x, y, w, h
	top2 = { 168, 24, 92, 88 }; // - (20,24) robot bmp size
	top3 = { 456, 24, 92, 88 };
	top4 = { 600, 24, 92, 88 };

	mid1 = { 168, 168, 92, 88 };
	mid2 = { 312, 168, 92, 88 };
	mid3 = { 456, 168, 92, 88 };

	low1 = { 24, 312, 92, 88 };
	low2 = { 168, 312, 92, 88 };
	low3 = { 456, 312, 92, 88 };
	low4 = { 600, 312, 92, 88 };

	addZonesToVector();

	time_bomb_launched = -10000.f;	// time from the last time a bomb was dropped by one of the aliens
}

void RobotSpawnBehaviourComponent::spawnRobots() {

	//1) Randomly choose how many robots are placed (max 11 robots)
	setNumberOfRobots();

	int spawnPerQuadrat;
	int offsetX, offsetY, x, y;

	for (int i = no_of_robots; i > 0; i--) {
		SDL_Rect spawnZone = getRandomRectangle(); //this zone is now removed from vector
		offsetX = std::rand() % 92 + 1;
		offsetY = std::rand() % 88 + 1;
		x = spawnZone.x + offsetX;
		y = spawnZone.y + offsetY;
		spawnPerQuadrat = std::rand() % 2 + 1;
		if (spawnPerQuadrat == 1 || i == 1) {
			Robot* robot = robots_pool->firstAvailable();
			robot->botType = checkBotType();
			robot->init(x, y);
			game_objects->insert(robot);
		}
		else if (spawnPerQuadrat == 2) {
			for (int j = 0; j < 2; j++) {
				Robot* robot = robots_pool->firstAvailable();
				robot->botType = checkBotType();
				robot->init(x, y);
				game_objects->insert(robot);
				SDL_Rect spawned{ x, y, 20, 24 };
				SDL_Rect newRobot = getNewRobotPosition(spawnZone, spawned);
				x = newRobot.x;
				y = newRobot.y;
			}
			i--;
		}
	}

	addZonesToVector(); //add all zones in again
}

Message RobotSpawnBehaviourComponent::checkBotType() {
	if (go->currentScore < 500) {
		return Message::YELLOWBOT;
	}
	else if (go->currentScore >= 500 && go->currentScore < 1500) {
		return Message::REDBOT;
	}
	else if (go->currentScore >= 1500 && go->currentScore < 3000){
		return Message::CYANBOT;
	}
}

void RobotSpawnBehaviourComponent::update(float dt) {
	if (checkBonus()) {
		go->send(Message::LEVEL_WIN); //draw bonus points on bottom right screen (as soon as no robot is left)
	}
}

void RobotSpawnBehaviourComponent::receive(Message m) {
	if (m == Message::NEW_ROOM) {
		if (checkBonus()) {
			go->send(Message::ADDBONUS); //add bonus points to score (after leaving room)
		}
		clearRobots();
		spawnRobots();
	}
}

bool RobotSpawnBehaviourComponent::checkBonus(){
	for (int i = 0; i < robots_pool->pool.size(); i++) {
		if (robots_pool->pool[i]->enabled) {
			return false;
		}
	}
	return true;
}

void RobotSpawnBehaviourComponent::clearRobots() {
	for (int i = 0; i < robots_pool->pool.size(); i++) {
		if (robots_pool->pool[i]->enabled) {
			robots_pool->pool[i]->enabled = false;
		}
	}
}

void RobotSpawnBehaviourComponent::setNumberOfRobots() {
	srand(time(NULL));
	//randomly between 1 and 11 robots
	no_of_robots = std::rand() % 11 + 1;
}

SDL_Rect RobotSpawnBehaviourComponent::getNewRobotPosition(SDL_Rect spawnZone, SDL_Rect existingRobot) {

	int offsetX, offsetY;
	offsetX = std::rand() % 92 + 1;
	offsetY = std::rand() % 88 + 1;
	SDL_Rect newRobot{ spawnZone.x + offsetX, spawnZone.y + offsetY, 20, 24 };
	while (SDL_HasIntersection(&existingRobot, &newRobot)) {
		offsetX = std::rand() % 92 + 1;
		offsetY = std::rand() % 88 + 1;
		newRobot = { spawnZone.x + offsetX, spawnZone.y + offsetY, 20, 24 };
	}
	return newRobot;
}

SDL_Rect RobotSpawnBehaviourComponent::getRandomRectangle() {
	int offset = (rand() / (float)RAND_MAX)* rectangles.size();
	SDL_Rect res;

	for (unsigned int i = 0; i < rectangles.size(); i++) {
		int index = (i + offset) % rectangles.size();
		res = rectangles[index];
		rectangles.erase(rectangles.begin() + index);
		return res;
	}
}

void RobotSpawnBehaviourComponent::addZonesToVector() {
	rectangles.clear();

	rectangles.push_back(top1);
	rectangles.push_back(top2);
	rectangles.push_back(top3);
	rectangles.push_back(top4);
	rectangles.push_back(mid1);
	rectangles.push_back(mid2);
	rectangles.push_back(mid3);
	rectangles.push_back(low1);
	rectangles.push_back(low2);
	rectangles.push_back(low3);
	rectangles.push_back(low4);
}