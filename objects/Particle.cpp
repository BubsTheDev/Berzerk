#include "Particle.h"

void Particle::init(Sprite* sprite, double x, double y, double xVel, double yVel, int lifetime) {
	this->x = x; 
	this->y = y;
	this->xVel = xVel; 
	this->yVel = yVel;
	this->sprite = sprite;
	framesLeft_ = lifetime;
}

void Particle::update(float dt) {
	if (!inUse()) 
		return;
	
	framesLeft_--;
	x += xVel * dt;
	y += yVel * dt;
	
	draw();
}

void Particle::draw() {
	if (sprite) {
		sprite->draw(int(x), int(y));
	}
}