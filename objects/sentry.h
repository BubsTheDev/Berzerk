#pragma once

#include "../GameObject.h"
#include "Player.h"
#include "SDL.h"
#include "../Component.h"

class Sentry : public GameObject {
public:
	double playerX, playerY, startX, startY;
	bool stop;

	virtual void init(double xPos, double yPos);

	virtual void receive(Message m);

	virtual void receive(Message m, GameObject* go);

};

