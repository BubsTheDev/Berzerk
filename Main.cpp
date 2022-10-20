#define _CRT_SECURE_NO_WARNINGS

#include "Avancezlib.h"
#include "Game.h"

const unsigned int	MAX_NUM_GAME_OBJECTS = 10000;

float game_speed = 1.f;		// speed of the game; it is increased each time all the aliens are hit
// it is also the score multiplier

int main(int argc, char** argv) {

	AvancezLib system;

	system.init(736, 500); //actual room size 736x448

	Game game;
	game.create(&system);
	game.init();
	
	float lastTime = system.getElapsedTime();
	while (system.update())
	{
		float newTime = system.getElapsedTime();
		float dt = newTime - lastTime;
		dt = dt * game_speed;
		lastTime = newTime;
		
		game.update(dt);

		game.draw();
	}

	// clean up
	game.destroy();
	system.destroy();

	return 0;
}