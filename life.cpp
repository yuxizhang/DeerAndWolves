#include "life.h"

#include "world.h"

Life::Life(LifeType type, World* world, int lifespan, float max_energy, Position pos) :
		type(type), world(world), kLifespan(lifespan), kMaxEnergy(max_energy),
		position(pos), age(0), energy(0), hunger(0), dead(false) {
	world->AddLife(this);
}

void Life::Update() {
	age++;
	if (age > kLifespan) {
		Kill();
		return;
	}
	energy = CalculateEnergy(age);
}

void Life::KillSelf() {
	Kill();
	world->SetBlank(position);
}

float Life::Kill() {
	float ret = energy;
	energy = 0;
	dead = true;
	return ret;
}