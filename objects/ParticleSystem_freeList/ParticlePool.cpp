#include "ParticlePool.h"

ParticlePool::ParticlePool() {
	// The first one is available.
	firstAvailable_ = &particles[0];

	// Each particle points to the next.
	for (int i = 0; i < POOL_SIZE - 1; i++) {
		particles[i].setNext(&particles[i + 1]);
	}

	// The last one terminates the list.
	particles[POOL_SIZE - 1].setNext(NULL);
}

void ParticlePool::init(Sprite* sprite) {
	this->sprite = sprite;
}

void ParticlePool::create(double x, double y, double xVel, double yVel, int lifetime) {
	srand(time(NULL));
	
	// Find an available particle.

	// Make sure the pool isn't full.
	assert(firstAvailable_ != NULL);

	// Remove it from the available list.
	Particle* newParticle = firstAvailable_;
	firstAvailable_ = newParticle->getNext();

	angle = std::rand() % 360 + 1;
	newParticle->init(sprite, x + std::rand() % 10, y + std::rand() % 10, xVel * cos(angle), yVel * sin(angle), lifetime);
}

void ParticlePool::update(float dt) {
	for (int i = 0; i < POOL_SIZE; i++) {
		if (particles[i].update(dt)) {
			// Add this particle to the front of the list.
			particles[i].setNext(firstAvailable_);
			firstAvailable_ = &particles[i];
		}
	}
}

