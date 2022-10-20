#pragma once

#include "../GameObject.h"
#include "../Component.h"
#include "SDL.h"

class Room : public GameObject {

public:

	virtual ~Room();

	virtual void init();

	virtual void receive(Message m);

};