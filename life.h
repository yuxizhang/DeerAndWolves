#ifndef LIFE_H
#define LIFE_H

#include "utils.h"

class World;

class Life {
public:
	float energy;
	bool dead;
	Position position;
	const LifeType type;

	Life(LifeType type, World* world, int lifespan, float max_energy, Position pos);

	virtual void Update();
	float Kill(); 

protected:
	World* world;

private:
	const int kLifespan;
	const float kMaxEnergy;
	int age;

	float CalculateEnergy(int age) {
		return 4.0f * kMaxEnergy * (float) (age * (kLifespan - age))
			/ (float) (kLifespan * kLifespan);
	}
};

#endif