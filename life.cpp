#include "life.h"

#include "world.h"

Life::Life(LifeType type, World* world, int lifespan, float max_energy, Position pos) :
		type(type), world(world), kLifespan(lifespan), kMaxEnergy(max_energy),
		position(pos), age(0), energy(0), hunger(0), dead(false) {
	world->AddLife(this);
}

void Life::Update() {
	cout << "life update" << endl;
	age++;
	if (age > kLifespan) {
		Kill();
		return;
	}
	energy = CalculateEnergy(age);
}

float Life::Kill() {
	float ret = energy;
	energy = 0;
	dead = true;
	return ret;
}