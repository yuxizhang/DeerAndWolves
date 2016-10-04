#ifndef ANIMAL_H
#define ANIMAL_H

#include <vector>
// #include "debug.h"
#include "life.h"
#include "utils.h"
#include "world.h"

using namespace std;

struct Node {
	Position pos;
	int parent;
	Node(Position pos, int parent) : pos(pos), parent(parent) {}
};

class Animal : protected Life {
public:
	Animal(LifeType type, World* world, int lifespan, float max_energy, Position pos); 
	~Animal();

	void Update();
	void GetEnergy(float energy);

protected:
	float strength;
	float hunger;
	// bool done;
	vector<Position> path;

	void FindFood(LifeType type);
	Position FindNearest(LifeType type);
	Position FindPath(const Position& target);
	bool MoveTo(const Position& target); 
};

#endif