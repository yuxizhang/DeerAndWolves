#ifndef ANIMAL_H
#define ANIMAL_H

#include <vector>
// #include "debug.h"
#include "life.h"
#include "utils.h"
#include "world.h"

using namespace std;

static const float kMoveStrength = 10;
static const float kHungerSpeed = 0.1;
static const float kHungerLevel = 0.2;

class Animal : protected Life {
public:
	Animal(LifeType type, World* world, int lifespan, float max_energy, Position pos); 
	virtual ~Animal();

	virtual void Update();
	void GainEnergy(float energy);

protected:
	float strength;
	float hunger;
	int vision;
	// bool done;
	vector<Position> path;

	void FindFood(LifeType type);

	Position FindNearest(LifeType type);
	Position FindPath(const Position& target);
	bool MoveTo(const Position& target); 
};

#endif