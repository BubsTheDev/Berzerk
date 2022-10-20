#pragma once

#include "objects/Robot.h"
#include "objects/Bullet.h"
#include "objects/Sentry.h"
#include "objects/Wall.h"
#include "objects/Player.h"
#include "components/PlayerBehaviourComponent.h"
#include "components/SentryBehaviourComponent.h"
#include "components/RobotBehaviourComponent.h"
#include "components/BulletBehaviourComponent.h"
#include "components/RobotSpawnBehaviourComponent.h"
#include "components/RoomBehaviourComponent.h"
#include "objects/RobotSpawn.h"
#include "objects/Room.h"
#include "objects/ParticlePool.h"

class Game : public GameObject {
	std::set<GameObject*> game_objects;	// http://www.cplusplus.com/reference/set/set/
	
	AvancezLib* system;

	ObjectPool<Robot> robots_pool;
	ObjectPool<Bullet> robotbullets_pool;
	ObjectPool<Bullet> playerbullets_pool;
	ObjectPool<Wall> wall_pool; 
	ObjectPool<Sentry> sentry_pool;
	ParticlePool particle_pool;

	Player* player;
	RobotSpawn* robotspawn;
	Room* room;

	Sprite* life_sprite;

	bool game_over;

	unsigned int score = 0;
	unsigned int bonus = 0;

public:

	virtual void create(AvancezLib* system);

	virtual void init();

	virtual void update(float dt);

	virtual void draw();

	unsigned int getScore();

	unsigned int getBonus();

	virtual void receive(Message m);

	bool isGameOver();

	virtual void destroy();

	private:
		const unsigned int	POINTS_PER_ROBOT = 50;
		float			game_speed = 1.0f;
		Message drawBonus;

		//For cheatmode
		CollideComponent* player_rbullet_collision;
		CollideComponent* player_robot_collision;
		CollideComponent* player_wall_collision;
		CollideComponent* player_sentry_collision;

		bool switchRobotWallCollide = false;
};