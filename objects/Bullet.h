#pragma once

#include "SDL.h"
#include "../GameObject.h"

class Bullet : public GameObject {

public:
	Message shootDirection;

	virtual void init(double xPos, double yPos);

	virtual void receive(Message m);

};