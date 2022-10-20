#include "Particle.h"

void Particle::init(Sprite* sprite, double x, double y, double xVel, double yVel, int lifetime) {
	state_.live.x = x;
	state_.live.y = y;
	state_.live.xVel = xVel;
	state_.live.yVel = yVel;
	this->sprite = sprite;
	framesLeft_ = lifetime;
}

bool Particle::update(float dt) {
	if (!inUse()) 
		return false;

	framesLeft_--;
	state_.live.x += state_.live.xVel * dt;
	state_.live.y += state_.live.yVel * dt;

	draw();

	return framesLeft_ == 0;
}

void Particle::draw() {
	if (sprite) {
		sprite->draw(int(state_.live.x), int(state_.live.y));
	}
}