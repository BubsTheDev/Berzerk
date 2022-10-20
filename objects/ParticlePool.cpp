#include "ParticlePool.h"

void ParticlePool::init(Sprite* sprite) {
	SDL_Log("ParticlePool::Init");
	this->sprite = sprite;
}

void ParticlePool::create(double x, double y, double xVel, double yVel, int lifetime) {
	// Find an available particle.
	SDL_Log("ParticlePool::Create");
	srand(time(NULL));

	for (int i = 0; i < POOL_SIZE; i++) {
		if (!particles[i].inUse()) {
			angle = std::rand() % 360 + 1;
			particles[i].init(sprite, x + std::rand() % 10, y + std::rand() % 10, xVel * cos(angle), yVel * sin(angle), lifetime);
			//return;
		}
	}
}

void ParticlePool::update(float dt) {
	for (int i = 0; i < POOL_SIZE; i++) {
		particles[i].update(dt);
	}
}
