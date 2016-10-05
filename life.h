#ifndef LIFE_H
#define LIFE_H

#include "utils.h"

class World;

class Life {
public:
	float energy;
	float hunger;
	bool dead;
	Position position;
	const LifeType type;

	Life(LifeType type, World* world, int lifespan, float max_energy, Position pos);
	virtual ~Life() {}

	virtual void Update();
	void KillSelf();
	float Kill();
	virtual void GainEnergy(float energy) {}

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