#ifndef DEER_H
#define DEER_H

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

class Deer : public Life {
public:
	Deer(World* world, int lifespan, float max_energy, Position pos); 
	~Deer();

	void Update();

private:
	float strength;
	// float hunger;
	// bool done;
	vector<Position> path;

	void EatGrass();
	Position FindNearest(LifeType type);
	Position FindPath(const Position& target);
	bool MoveTo(const Position& target); 
};

#endif