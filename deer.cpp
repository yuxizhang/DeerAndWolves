#include "deer.h"

Deer::Deer(World* world, int lifespan, float max_energy, Position pos) :
	Animal(DEER, world, lifespan, max_energy, pos) {}

void Deer::Update() {
	Animal::Update();
	cout << "before, deer energy: " << energy << endl;
	cout << "before, deer hunger: " << hunger << endl;
	cout << "before, deer strength: " << strength << endl;
	Animal::FindFood(GRASS);
	cout << "after, deer energy: " << energy << endl;
	cout << "after, deer hunger: " << hunger << endl;
	cout << "after, deer strength: " << strength << endl;
}