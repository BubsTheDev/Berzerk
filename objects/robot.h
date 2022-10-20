#pragma once

#include "../GameObject.h"
#include "../Component.h"
#include "ParticlePool.h"

class Robot : public GameObject {

public:
	double playerX, playerY;
	Message botType;
	AiCollideComponent* no_death_coll;
	CollideComponent* death_coll;

	virtual void init(double xPos, double yPos);

	virtual void receive(Message m);

	virtual void receive(Message m, GameObject* go);

};