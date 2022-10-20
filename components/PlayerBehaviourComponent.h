#pragma once
#include "../objects/Bullet.h"
#include "../objects/Player.h"
#include "../objects/Room.h"
#include "../Message.h"
#include "../ObjectPool.h"

class PlayerBehaviourComponent : public Component {
	
public:

	virtual ~PlayerBehaviourComponent() {}

	virtual void create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<Bullet>* bullet_pool);

	virtual void init();

	virtual void update(float dt);

	virtual void receive(Message m);

private:
	void checkNewLevel();

	void move(float move, AvancezLib::KeyStatus keys);

	bool canFire();

	const unsigned int	NUM_LIVES = 2;
	float time_fire_pressed;	
	ObjectPool<Bullet>* bullet_pool;
};