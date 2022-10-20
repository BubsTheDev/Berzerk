#include "Component.h"
#include "GameObject.h"
#include "Avancezlib.h"

void Component::create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects)
{
	this->go = go;
	this->system = system;
	this->game_objects = game_objects;
}

void RenderComponent::create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, const char* sprite_name) {
	Component::create(system, go, game_objects);

	sprite = system->createSprite(sprite_name);
}

Sprite* RenderComponent::changeSprite(const char* sprite_name) {
	if (sprite != NULL)
		sprite->destroy();
	sprite = system->createSprite(sprite_name);
	return sprite;
}

void RenderComponent::update(float dt) {
	if (!go->enabled)
		return;

	if (sprite)
		sprite->draw(int(go->horizontalPosition), int(go->verticalPosition));
}

void RenderComponent::destroy()
{
	if (sprite != NULL)
		sprite->destroy();
	sprite = NULL;
}


void CollideComponent::create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<GameObject>* coll_objects)
{
	Component::create(system, go, game_objects);
	this->coll_objects = coll_objects;
}

void CollideComponent::create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, GameObject* go0) {
	Component::create(system, go, game_objects);
	ObjectPool<GameObject> obj;
	obj.deallocate();
	obj.pool.push_back(go0);

	this->coll_objects = &obj;
}

void CollideComponent::update(float dt) {
	for (unsigned int i = 0; i < coll_objects->pool.size(); i++) {
		GameObject* go0 = coll_objects->pool[i];
		if (go0->enabled && go != go0) {
			if ((go0->horizontalPosition > go->horizontalPosition - 16) &&
				(go0->horizontalPosition < go->horizontalPosition + 16) &&
				(go0->verticalPosition   > go->verticalPosition - 16) &&
				(go0->verticalPosition   < go->verticalPosition + 16)) {
				go->receive(Message::HIT);
				go0->receive(Message::HIT);
			}
		}
	}
}

void AiCollideComponent::create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<GameObject>* coll_objects) {
		Component::create(system, go, game_objects);
		this->coll_objects = coll_objects;
	}
void AiCollideComponent::update(float dt) {
	SDL_Rect robot = { go->horizontalPosition, go->verticalPosition, 20, 24 };
	
		for (unsigned int i = 0; i < coll_objects->pool.size(); i++) {
			GameObject* go0 = coll_objects->pool[i];
			SDL_Rect wall = { go0->horizontalPosition, go0->verticalPosition, 16, 16 };
			if (go0->enabled && go != go0) {
				if (SDL_HasIntersection(&robot, &wall)) {
					go->receive(Message::WALL, go0);
					go0->receive(Message::WALL, go);
				}
				else {
					go->receive(Message::NO_MSG, go0);
					go0->receive(Message::NO_MSG, go);
				}
			}	
		}
};