#pragma once

#include <set>
#include "ObjectPool.h"
#include "GameObject.h"
#include "Avancezlib.h"
#include <ctime>

class GameObject;
class AvancezLib;
class Sprite;

class Component{
protected:
	AvancezLib* system;
	GameObject* go;	// the game object this component is part of
	std::set<GameObject*>* game_objects;	// the global container of game objects

public:
	virtual ~Component() {}

	virtual void create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects);

	virtual void init() {}
	virtual void update(float dt) = 0;
	//virtual void Receive(int message) {}
	virtual void receive(Message m) {}
	virtual void receive(Message m, GameObject* go) {}
	virtual void destroy() {}

	const float			PLAYER_SPEED = 75.0f;
	float			ROBOT_SPEED = PLAYER_SPEED / 2;
	float				SENTRY_SPEED = PLAYER_SPEED / 2;
	float				time_bullet_launched = -10000.f;
	const float			BULLET_TIME_INTERVAL = 1.25f;
	const float			game_speed = 1.0f;
	const float			FIRE_TIME_INTERVAL = .5f;
	const float			BULLET_SPEED = 200.0f;
};


class RenderComponent : public Component {
	Sprite* sprite;

public:

	virtual void create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, const char* sprite_name);
	virtual Sprite* changeSprite(const char* sprite_name);
	virtual void update(float dt);
	virtual void destroy();

	Sprite* getSprite() { return sprite; }
};


class CollideComponent : public Component
{
	ObjectPool<GameObject>* coll_objects; // collision will be tested with these objects
public:
	virtual void create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<GameObject>* coll_objects);
	virtual void create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, GameObject* go0);
	virtual void update(float dt);

};

class AiCollideComponent : public Component {
	ObjectPool<GameObject>* coll_objects; // collision will be tested with these objects

public:
	virtual void create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<GameObject>* coll_objects);
	virtual void update(float dt);
};