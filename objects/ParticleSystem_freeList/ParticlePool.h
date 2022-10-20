#pragma once
#include "Particle.h"
#include <cassert>
#include <cstdlib>
#include <math.h>
#include <ctime>

class ParticlePool {
public:
	ParticlePool();

	void init(Sprite* sprite);

	void create(double x, double y, double xVel, double yVel, int lifetime);

	void update(float dt);

private:
	Particle* firstAvailable_;

	static const int POOL_SIZE = 50;
	Particle particles[POOL_SIZE];
	Sprite* sprite;
	double angle;
};