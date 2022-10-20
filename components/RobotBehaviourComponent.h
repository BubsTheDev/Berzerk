#pragma once

#include "../Component.h"
#include "../Message.h"
#include "../ObjectPool.h"
#include "../objects/Bullet.h"
#include "../objects/Player.h"
#include "../objects/Robot.h"
#include <ctime>

class RobotBehaviourComponent : public Component {
public:

	virtual ~RobotBehaviourComponent() {}

	virtual void create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<Bullet>* bullets_pool, ParticlePool* particle_pool);

	virtual void update(float dt);

	virtual void receive(Message m);

	virtual void receive(Message m, GameObject* go);

private:
	void checkRobotPosition();

	void fire(Message direction, int x, int y);

	bool canFire();

	void setTrackStage();

	Robot* robot;
	Message trackState;
	bool stop = false;
	ObjectPool<Bullet>* bullets_pool;
	ParticlePool* particle_pool;
};