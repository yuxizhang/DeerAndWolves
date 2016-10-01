#ifndef GRASS_H
#define GRASS_H

#include <iostream>
#include "life.h"
#include "utils.h"

using namespace std;

class Grass : public Life {
public:
	Grass(World* world, int lifespan, float max_energy, Position pos) :
			Life(GRASS, world, lifespan, max_energy, pos) {}

	void Update() {
		Life::Update();
		cout << "grass update" << endl;
	}
};

#endif