#include "Room.h"

Room::~Room()	{
	SDL_Log("Room::~Room"); 
}

void Room::init() {
	SDL_Log("Room::Init");
	GameObject::init();
}

void Room::receive(Message m) {
	components[0]->receive(m); //Behaviour
	/*if (!enabled)
	return; */
}