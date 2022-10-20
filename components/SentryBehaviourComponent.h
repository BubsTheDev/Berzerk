#pragma once

#include "../Component.h"
#include "../objects/Sentry.h"

class SentryBehaviourComponent : public Component {
public:

	virtual ~SentryBehaviourComponent() {}

	virtual void create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects);

	virtual void update(float dt);

	virtual void receive(Message m);
};