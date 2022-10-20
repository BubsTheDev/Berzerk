#pragma once
#include "Particle.h"
#include <vector>

class ParticlePool {
public:
	void init(Sprite* sprite);

	void create(double x, double y, double xVel, double yVel, int lifetime);

	void update(float dt);

private:
	static const int POOL_SIZE = 50;
	Particle particles[POOL_SIZE];
	AvancezLib* system;
	Sprite* sprite;
	double angle;
};