#ifndef DEER_H
#define DEER_H

#include "animal.h"
#include "utils.h"

class Deer : public Animal {
public:
	Deer(World* world, int lifespan, float max_energy, Position pos);
	~Deer() {
		Animal::~Animal();
	}
	void Update();
private:
	bool DodgeEnemy(LifeType type);
	Position RunAway(const Position& enemy);
};


#endif