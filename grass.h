#ifndef GRASS_H
#define GRASS_H

#include "life.h"
#include "utils.h"

using namespace std;

class Grass : public Life {
public:
	Grass(World* world, int lifespan, float max_energy, Position pos) :
			Life(GRASS, world, lifespan, max_energy, pos) {}

	~Grass() {
		Life::~Life();
	}

	void Update() {
		Life::Update();
	}

	void GetEnergy(float energy) {
		// For grass, do nothing
	}
};

#endif