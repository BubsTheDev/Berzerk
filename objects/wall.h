#pragma once

#include "../GameObject.h"

class Wall : public GameObject {
public:
	virtual void init(double xPos, double yPos);

	void disable();

};
