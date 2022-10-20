#pragma once

#include "Bullet.h"
#include "../GameObject.h"
#include "../Component.h"

// the main player
class Player : public GameObject {
public:

	int lives;	// it's game over when goes below zero 
	double startX, startY;

	virtual ~Player();

	virtual void init();

	virtual void receive(Message m);

private:
	void removeLife();

	const unsigned int	NUM_LIVES = 2;
	
};
