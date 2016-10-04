#ifndef DEER_H
#define DEER_H

#include "animal.h"
#include "utils.h"

class Deer : private Animal {
public:
	Deer(World* world, int lifespan, float max_energy, Position pos);
	void Update();
};


#endif