// GameObject represents objects which moves are drawn
#pragma once
#include <vector>
#include "Message.h"
#include "ObjectPool.h"

class Component;

class GameObject {
protected:
	
	std::vector<Component*> components;

public:
	const int BONUS_POINTS = 10;

	double horizontalPosition;
	double verticalPosition;

	unsigned int currentScore;
	unsigned int currentBonus;

	bool enabled;
	std::vector<GameObject*> receivers;
	virtual ~GameObject();

	virtual void create();
	virtual void addComponent(Component* component);
	virtual void popComponent();
	int getComponentSize() { return components.size(); };

	virtual void init();
	virtual void update(float dt);
	virtual void destroy();
	virtual void addReceiver(GameObject* go);
	//virtual void addReceiver(std::vector<GameObject*> receivers);
	virtual void receive(Message m) {}
	virtual void receive(Message m, GameObject* go) {}
	virtual void receive(Message m, ObjectPool<GameObject>* pool) {}
	void send(Message m);
	void send(Message m, GameObject* go);
	void send(Message m, ObjectPool<GameObject>* pool);

private:
	
};