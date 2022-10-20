#include "GameObject.h"
#include "Component.h"
#include "Avancezlib.h"

void GameObject::create() {
	SDL_Log("GameObject::Create");

	enabled = false;
}

void GameObject::addComponent(Component* component) {
	components.push_back(component);
}

void GameObject::popComponent() {
	components.pop_back();
}

void GameObject::init() {
	//SDL_Log("GameObject::Init");

	for (auto it = components.begin(); it != components.end(); it++)
		(*it)->init();
	enabled = true;
}

void GameObject::update(float dt) {
	if (!enabled)
		return;

	for (auto it = components.begin(); it != components.end(); it++)
		(*it)->update(dt);
}

void GameObject::destroy() {
	for (auto it = components.begin(); it != components.end(); it++)
		(*it)->destroy();
}

GameObject::~GameObject() {
	SDL_Log("GameObject::~GameObject");
}

void GameObject::addReceiver(GameObject* go) {
	receivers.push_back(go);
}

void GameObject::send(Message m) {
	for (auto i = 0; i < receivers.size(); i++) {
		if (!receivers[i]->enabled)
			continue;

		receivers[i]->receive(m);
	}
}

void GameObject::send(Message m, GameObject* go) {
	for (auto i = 0; i < receivers.size(); i++) {
		if (!receivers[i]->enabled)
			continue;

		receivers[i]->receive(m, go);
	}
}

void GameObject::send(Message m, ObjectPool<GameObject>* pool) {
	for (auto i = 0; i < receivers.size(); i++) {
		if (!receivers[i]->enabled)
			continue;

		receivers[i]->receive(m, pool);
	}
}