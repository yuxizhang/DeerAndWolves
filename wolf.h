#ifndef WOLF_H
#define WOLF_H

#include "animal.h"

class Wolf : public Animal {
public:
	Wolf(World* world, int lifespan, float max_energy, Position pos):
			Animal(WOLF, world, lifespan, max_energy, pos) {
		vision = 100;
		moved =false;
	}
	~Wolf() {
		Animal::~Animal();
	}
	void Update() {
		Animal::Update();
		if (dead) return;
		if (!moved) moved = Animal::FindFood(DEER);
		if (!moved && Life::IsMature()) moved = Animal::FindMate();
		// cout << "after, wolf energy: " << energy << endl;
		// cout << "after, wolf hunger: " << hunger << endl;
		// cout << "after, wolf strength: " << strength << endl;
	}
};

#endif
