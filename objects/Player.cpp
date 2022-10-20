#include "Player.h"

Player::~Player()	{ 
	SDL_Log("Player::~Player"); 
}

void Player::init() {
	SDL_Log("Player::Init");
	GameObject::init();

	lives = NUM_LIVES;
}

void Player::receive(Message m) {
	if (m == Message::HIT) {
		SDL_Log("Player::Hit!");
		removeLife();
		components[0]->receive(Message::HIT);

		if (lives < 0)
			send(Message::GAME_OVER);
	}
	if (m == Message::NEW_ROOM)
		components[0]->receive(Message::NEW_ROOM);
}

void Player::removeLife() {
	lives--;
	SDL_Log("remaining lives %d", lives);
}