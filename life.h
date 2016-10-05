#ifndef LIFE_H
#define LIFE_H

#include "utils.h"

class World;

class Life {
public:
	float energy;
	float hunger;
	bool dead;
	bool moved;
	int id;
	Position position;
	const LifeType type;

	Life(LifeType type, World* world, int lifespan, float max_energy, Position pos);
	virtual ~Life() {}

	virtual void Update();
	void KillSelf();
	float Kill();
	virtual void GainEnergy(float energy) {}
	bool IsMature() {
		return age > kLifespan * 0.2;
	}

protected:
	World* world;

private:
	const float kMaxEnergy;
	int age;
	const int kLifespan;

	float CalculateEnergy(int age) {
		return 4.0f * kMaxEnergy * (float) (age * (kLifespan - age))
			/ (float) (kLifespan * kLifespan);
	}
};

#endif