#include "deer.h"

#include <stdlib.h> 

Deer::Deer(World* world, int lifespan, float max_energy, Position pos) :
		Animal(DEER, world, lifespan, max_energy, pos) {
	vision = 10;
}

void Deer::Update() {
	Animal::Update();
	// cout << "dead " << dead << endl;
	if (dead) return;
	bool moved = DodgeEnemy(WOLF);
	Animal::FindFood(GRASS);

// 	cout << "deer updated" << endl;
// 	cout << "deer energy: " << energy << endl;
// 	cout << "deer hunger: " << hunger << endl;
// 	cout << "deer strength: " << strength << endl;
}

bool Deer::DodgeEnemy(LifeType type) {
	bool moved = false;
	Position enemy_pos = FindNearest(type);
	if (enemy_pos.IsValid() && position.Dist(enemy_pos) < vision) {
		while (strength > kMoveStrength) {
			Position next_pos = RunAway(enemy_pos);
			cout << "next pos: " << next_pos.x << " " << next_pos.y << endl;
			if (!MoveTo(next_pos)) break;
			moved = true;
		}
	}
	return moved;
}

Position Deer::RunAway(const Position& enemy) {
	int dirx = GetSign(position.x - enemy.x);
	int diry = GetSign(position.y - enemy.y);
	int dx[4], dy[4];
	if (dirx == 0) {
		dx[0] = 0; dx[1] = 1; dx[2] = -1; dx[3] = 0;
		dy[0] = diry; dy[1] = 0; dy[2] = 0; dy[3] = -diry;
	} else if (diry == 0) {
		dx[0] = dirx; dx[1] = 0; dx[2] = 0; dx[3] = -dirx;
		dy[0] = 0; dy[1] = 1; dy[2] = -1; dy[3] = 0;
	} else {
		dx[0] = dirx; dx[1] = 0; dx[2] = -dirx; dx[3] = 0;
		dy[0] = 0; dy[1] = diry; dy[2] = 0; dy[3] = -diry;
	}
	for (int k = 0; k < 4; ++k) {
		Position newpos(position.x + dx[k], position.y + dy[k]);
		if (newpos.IsValid() && !world->IsAnimal(newpos)) return newpos;
	}
	return Position(-1, -1);
}