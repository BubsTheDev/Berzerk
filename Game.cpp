#include "Game.h"

void Game::create(AvancezLib* system) {
	SDL_Log("Game::Create");

	this->system = system;	
	
	particle_pool.init(system->createSprite("data/particle.bmp"));

	sentry_pool.create(1);
	SentryBehaviourComponent* sentry_behaviour = new SentryBehaviourComponent();
	sentry_behaviour->create(system, sentry_pool.pool[0], &game_objects);
	RenderComponent* sentry_render = new RenderComponent();
	sentry_render->create(system, sentry_pool.pool[0], &game_objects, "data/sentry.bmp");
	sentry_pool.pool[0]->create();
	sentry_pool.pool[0]->addComponent(sentry_behaviour);
	sentry_pool.pool[0]->addComponent(sentry_render);
	game_objects.insert(sentry_pool.pool[0]);

	player = new Player();
	PlayerBehaviourComponent* player_behaviour = new PlayerBehaviourComponent();
	player_behaviour->create(system, player, &game_objects, &playerbullets_pool);
	RenderComponent* player_render = new RenderComponent();
	player_render->create(system, player, &game_objects, "data/player.bmp");
	player_rbullet_collision = new CollideComponent();
	player_rbullet_collision->create(system, player, &game_objects, (ObjectPool<GameObject>*)&robotbullets_pool);
	player_robot_collision = new CollideComponent();
	player_robot_collision->create(system, player, &game_objects, (ObjectPool<GameObject>*)&robots_pool);
	player_wall_collision = new CollideComponent();
	player_wall_collision->create(system, player, &game_objects, (ObjectPool<GameObject>*)&wall_pool);
	player_sentry_collision = new CollideComponent();
	player_sentry_collision->create(system, player, &game_objects, (ObjectPool<GameObject>*)&sentry_pool);

	player->create();
	player->addComponent(player_behaviour);
	player->addComponent(player_render);
	player->addComponent(player_rbullet_collision);
	player->addComponent(player_robot_collision);
	player->addComponent(player_wall_collision);
	player->addComponent(player_sentry_collision);
	player->addReceiver(this);
	game_objects.insert(player);

	wall_pool.create(193); //64 tiles for the random positions and 120 for static background + 8 for possible closed exits
	for (auto wall = wall_pool.pool.begin(); wall != wall_pool.pool.end(); wall++) {
		RenderComponent* render = new RenderComponent();
		render->create(system, *wall, &game_objects, "data/wall.bmp");
		(*wall)->create();
		(*wall)->addComponent(render);
	}

	room = new Room();
	RoomBehaviourComponent* room_behaviour = new RoomBehaviourComponent();
	room_behaviour->create(system, room, &game_objects, &wall_pool);
	room->create();
	room->addComponent(room_behaviour);

	playerbullets_pool.create(20);
	for (auto pbullet = playerbullets_pool.pool.begin(); pbullet != playerbullets_pool.pool.end(); pbullet++) {
		BulletBehaviourComponent* behaviour = new BulletBehaviourComponent();
		behaviour->create(system, *pbullet, &game_objects);
		RenderComponent* render = new RenderComponent();
		render->create(system, *pbullet, &game_objects, "data/pbullet.bmp");
		CollideComponent* bullet_wall_collision = new CollideComponent();
		bullet_wall_collision->create(system, *pbullet, &game_objects, (ObjectPool<GameObject>*)&wall_pool);
		CollideComponent* bullet_bullet_collision = new CollideComponent();
		bullet_bullet_collision->create(system, *pbullet, &game_objects, (ObjectPool<GameObject>*)&robotbullets_pool);
		CollideComponent* bullet_sentry_collision = new CollideComponent();
		bullet_sentry_collision->create(system, *pbullet, &game_objects, (ObjectPool<GameObject>*)&sentry_pool);
		(*pbullet)->create();
		(*pbullet)->addComponent(behaviour);
		(*pbullet)->addComponent(render);
		(*pbullet)->addComponent(bullet_wall_collision);
		(*pbullet)->addComponent(bullet_bullet_collision);
		(*pbullet)->addComponent(bullet_sentry_collision);
	}
	robotbullets_pool.create(5);
	for (auto bullet = robotbullets_pool.pool.begin(); bullet != robotbullets_pool.pool.end(); bullet++) {
		BulletBehaviourComponent* behaviour = new BulletBehaviourComponent();
		behaviour->create(system, *bullet, &game_objects);
		RenderComponent* render = new RenderComponent();
		render->create(system, *bullet, &game_objects, "data/rbullet.bmp");
		CollideComponent* bullet_wall_collision = new CollideComponent();
		bullet_wall_collision->create(system, *bullet, &game_objects, (ObjectPool<GameObject>*)&wall_pool);
		CollideComponent* bullet_sentry_collision = new CollideComponent();
		bullet_sentry_collision->create(system, *bullet, &game_objects, (ObjectPool<GameObject>*)&sentry_pool);
		(*bullet)->create();
		(*bullet)->addComponent(behaviour);
		(*bullet)->addComponent(render);
		(*bullet)->addComponent(bullet_wall_collision);
		(*bullet)->addComponent(bullet_sentry_collision);
	}

	robotspawn = new RobotSpawn();
	RobotSpawnBehaviourComponent* robotspawn_behaviour = new RobotSpawnBehaviourComponent();
	robotspawn_behaviour->create(system, robotspawn, &game_objects, &robots_pool, &robotbullets_pool);
	robotspawn->create();
	robotspawn->addComponent(robotspawn_behaviour);
	robotspawn->addReceiver(this);
	robotspawn->addReceiver(sentry_pool.pool[0]);
	game_objects.insert(robotspawn);

	robots_pool.create(11);
	for (auto robot = robots_pool.pool.begin(); robot != robots_pool.pool.end(); robot++) {
		RobotBehaviourComponent* robot_behaviour = new RobotBehaviourComponent();
		robot_behaviour->create(system, *robot, &game_objects, &robotbullets_pool, &particle_pool);
		RenderComponent* robot_render = new RenderComponent();
		robot_render->create(system, *robot, &game_objects, "data/yellowbot.bmp");
		CollideComponent* robot_rbullet_coll = new CollideComponent();
		robot_rbullet_coll->create(system, *robot, &game_objects, (ObjectPool<GameObject>*)&robotbullets_pool);
		CollideComponent* robot_pbullet_coll = new CollideComponent();
		robot_pbullet_coll->create(system, *robot, &game_objects, (ObjectPool<GameObject>*)&playerbullets_pool);
		CollideComponent* robot_robot_coll = new CollideComponent();
		robot_robot_coll->create(system, *robot, &game_objects, (ObjectPool<GameObject>*)&robots_pool);
		CollideComponent* robot_sentry_coll = new CollideComponent();
		robot_sentry_coll->create(system, *robot, &game_objects, (ObjectPool<GameObject>*)&sentry_pool);
		AiCollideComponent* robot_wall_nodeath = new AiCollideComponent();
		robot_wall_nodeath->create(system, *robot, &game_objects, (ObjectPool<GameObject>*)&wall_pool);
		CollideComponent* robot_wall_death = new CollideComponent();
		robot_wall_death->create(system, *robot, &game_objects, (ObjectPool<GameObject>*)&wall_pool);
		(*robot)->death_coll = robot_wall_death;
		(*robot)->no_death_coll = robot_wall_nodeath;

		(*robot)->create();
		(*robot)->addComponent(robot_behaviour);
		(*robot)->addComponent(robot_render);
		(*robot)->addComponent(robot_rbullet_coll);
		(*robot)->addComponent(robot_pbullet_coll);
		(*robot)->addComponent(robot_robot_coll);
		(*robot)->addComponent(robot_sentry_coll);
		(*robot)->addComponent(robot_wall_death);
		//(*robot)->addComponent(robot_wall_nodeath);	
		(*robot)->addReceiver(this);
		room->addReceiver(*robot);
		player->addReceiver(*robot); //player needs to send position to robot
	}

	room->addReceiver(robotspawn); // room can send messages to robotspawn
	room->addReceiver(sentry_pool.pool[0]);
	room->addReceiver(player);
	room->addReceiver(this);

	player->addReceiver(room);
	player->addReceiver(sentry_pool.pool[0]);

	game_objects.insert(room);

	life_sprite = system->createSprite("data/player.bmp");

	score = 0;
}

void Game::init() {
	player->init();
	robotspawn->init();
	room->init();
	sentry_pool.pool[0]->init(-32.0, -32.0);

	enabled = true;
	game_over = false;
}

void Game::update(float dt) {
	if (isGameOver())
		dt = 0.f;

	for (auto go = game_objects.begin(); go != game_objects.end(); go++) {
		(*go)->update(dt);
		(*go)->currentScore = score;		
	}

	particle_pool.update(dt);

	// modes
	if (system->godmode == true) { // disable collision for player
		if (player->getComponentSize() > 2) {
			player->popComponent();
		}
	}
	else if (system->godmode == false) { // enable collision for player
		if (player->getComponentSize() == 2) {
			player->addComponent(player_rbullet_collision);
			player->addComponent(player_robot_collision);
			player->addComponent(player_wall_collision);
			player->addComponent(player_sentry_collision);
		}
	}
	if (system->aiwalldeath == false) { //disable death at wall hit
		if (switchRobotWallCollide == false) {
			for (auto robot = robots_pool.pool.begin(); robot != robots_pool.pool.end(); robot++) {
				(*robot)->popComponent();
				(*robot)->addComponent((*robot)->no_death_coll);
			}
			switchRobotWallCollide = true;
		}
	}
	else if (system->aiwalldeath == true) {
		if (switchRobotWallCollide == true) {
			for (auto robot = robots_pool.pool.begin(); robot != robots_pool.pool.end(); robot++) {
				(*robot)->popComponent();
				(*robot)->addComponent((*robot)->death_coll);
			}
			switchRobotWallCollide = false;
		}
	}
}

void Game::draw() {
	char msg[1024];
	sprintf_s(msg, "%07d", getScore());
	system->drawText(180, 470, msg);

	if (drawBonus == Message::LEVEL_WIN) {
		sprintf_s(msg, "Bonus: %03d", getBonus());
		system->drawText(510, 470, msg);
		drawBonus = Message::NO_MSG;
	}

	for (int i = 0; i < player->lives; i++)
		life_sprite->draw(i * 36 + 20, 460);

	if (isGameOver()) {
		sprintf_s(msg, "*** G A M E  O V E R***");
		system->drawText(300, 470, msg);
	}
}

unsigned int Game::getScore() {
	return score;
}

unsigned int Game::getBonus() {
	return bonus;
}

void Game::receive(Message m) {
	if (m == Message::GAME_OVER)
		game_over = true;

	if (m == Message::ROBOT_HIT) {
		score += POINTS_PER_ROBOT;
		bonus += 10;
	}
	if (m == Message::ADDBONUS) {
		score += bonus;
	}
	if (m == Message::NEW_ROOM) {
		bonus = 0;
	}
	if (m == Message::LEVEL_WIN) {
		drawBonus = m;
	}

}

bool Game::isGameOver() {
	return game_over;
}

void Game::destroy() {
	SDL_Log("Game::Destroy");

	for (auto go = game_objects.begin(); go != game_objects.end(); go++)
		(*go)->destroy();

	life_sprite->destroy();

	robots_pool.destroy();
	wall_pool.destroy();
	playerbullets_pool.destroy();
	robotbullets_pool.destroy();
	sentry_pool.destroy();

	delete robotspawn;
	delete player;
	delete room;
}
