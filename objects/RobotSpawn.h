#pragma once

#include "../GameObject.h"
#include "SDL.h"
#include "../Component.h"

class RobotSpawn : public GameObject {
public:

	virtual ~RobotSpawn();

	virtual void init();

	virtual void receive(Message m);
};