#pragma once

#include "../Avancezlib.h"
#include <ctime>
#include <cstdlib>
#include <Math.h>

class Particle {
public:
	Particle() : framesLeft_(0) {}
	~Particle() {  };

	void init(Sprite* sprite, double x, double y, double xVel, double yVel, int lifetime);

	void update(float dt);

	bool inUse() const { return framesLeft_ > 0; }

	void draw();

private:
	int framesLeft_;
	double x, y;
	double xVel, yVel;
	double velocity, direction, angle;
	Sprite* sprite;
};