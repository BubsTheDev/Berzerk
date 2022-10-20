#pragma once

#include "../Component.h"
#include "../objects/Bullet.h"

class BulletBehaviourComponent : public Component {
public:
	virtual void update(float dt);
};