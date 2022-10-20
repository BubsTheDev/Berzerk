#pragma once

#include <vector>

template <class T>
class ObjectPool {
public:

	void create(unsigned int num_objects/*, AvancezLib* system*/) {
		deallocate();

		for (unsigned int i = 0; i < num_objects; i++)
		{
			T* t = new T();
			//t->Create(system);
			pool.push_back(t);
		}
	}

	void destroy() {
		for (auto it = pool.begin(); it != pool.end(); it++)
			(*it)->destroy();
	}

	void deallocate() {
		SDL_Log("ObjectPool::Deallocating ");
		for (std::vector<T*>::iterator it = pool.begin(); it != pool.end(); it++)
			delete*it;
	}

	~ObjectPool(){
		SDL_Log("ObjectPool::~ObjectPool");
		deallocate();
	}

	T* firstAvailable() {
		for (std::vector<T*>::iterator it = pool.begin(); it != pool.end(); it++)
		if (!(**it).enabled)
			return (*it);

		// if it reaches this point, there is no available rocket in the pool
		return NULL;
	}

	// select a random, enabled element in the object pool
	T* selectRandom() {
		int offset = (rand() / (float)RAND_MAX)* pool.size();

		for (int i = 0; i < pool.size(); i++) {
			int index = (i + offset) % pool.size();

			if (pool[index]->enabled)
				return pool[index];
		}

		return NULL;
	}

	int countEnabled() {
		int val = 0;
		for (std::vector<T*>::iterator it = pool.begin(); it != pool.end(); it++)
		if ((**it).enabled)
			val++;
		return val;
	}

	std::vector<T*> pool;

};