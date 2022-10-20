#pragma once

#include "../Avancezlib.h"

class Particle {
public:
	Particle() : framesLeft_(0) {}
	~Particle() {  };

	void init(Sprite* sprite, double x, double y, double xVel, double yVel, int lifetime);

	Particle* getNext() const { return state_.next; }
	void setNext(Particle* next) { state_.next = next; }

	double getX() { return state_.live.x; }

	bool update(float dt);

	bool inUse() const { return framesLeft_ > 0; }

	void draw();

private:
	int framesLeft_;
	Sprite* sprite;

	union {
		// State when it's in use.
		struct {
			double x, y;
			double xVel, yVel;
		} live;
		// State when it's available.
		Particle* next;
	} state_;

};