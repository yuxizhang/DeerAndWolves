#include "world.h"

#include <stdio.h>      /* NULL */
#include "life.h"
#include "grass.h"

World::World() {
	cells = new Life**[kMapSize];
	for (int i = 0; i < kMapSize; ++i) {
		cells[i] = new Life*[kMapSize];
		for (int j = 0; j < kMapSize; ++j) {
			cells[i][j] = NULL;
		}
	}
	grass_list.clear();
	deer_list.clear();
}

World::~World() {
	// Free grass space
	list<Life*>::iterator it = grass_list.begin();
	while (it != grass_list.end()) {
		free(*it);
		++it;
	}
	// Free deer space
	it = deer_list.begin();
	while (it != deer_list.end()) {
		free(*it);
		++it;
	}
}

void World::Update() {
	// for (int i = 0; i < kMapSize; ++i) {
	// 	for (int j = 0; j < kMapSize; ++j) {
	// 		if (cells[i][j]) {
	// 			cells[i][j]->Update();
	// 		}
	// 	}
	// }
	cout << "grass turn begin" << endl;
	NewGrass();
	// Update grass
	list<Life*>::iterator it = grass_list.begin();
	while (it != grass_list.end()) {
		(*it)->Update();
		if ((*it)->dead) {
			free(*it);
			it = grass_list.erase(it);
		} else {
			++it;
		}
	}
	cout << "grass turn end" << endl;
	PrintMap();
	cout << "deer turn begin" << endl;
	cout << "deer amount: " << deer_list.size() << endl;
	// Update deer
	it = deer_list.begin();
	while (it != deer_list.end()) {
		(*it)->Update();
		++it;
	}
	cout << "deer turn end" << endl;
	PrintMap();
}

void World::NewGrass() {
	int lifespan = 100;
	int max_energy = 50;
	int max_try = 10;
	int x = rand() % kMapSize, y = rand() % kMapSize;
	while (cells[x][y] != NULL && max_try > 0) {
		x = rand() % kMapSize;
		y = rand() % kMapSize;
		--max_try;
	}
	if (max_try == 0) return;
	cells[x][y] = new Grass(this, lifespan, max_energy, Position(x, y));
}

void World::SetBlank(Position pos) {
	cells[pos.x][pos.y] = NULL;
}

void World::AddLife(Life* life) {
	cells[life->position.x][life->position.y] = life;
	switch (life->type) {
		case GRASS :
			grass_list.push_back(life);
			break;
		case DEER :
			deer_list.push_back(life);
			break;
		default :
			break;
	}
}

void World::MoveLife(Position origin, Position target) {
	if (!IsAnimal(origin) || IsAnimal(target)) {
		cout << "WARNING: cannot move life." << endl;
		return;
	}
	if (!IsBlank(target)) {
		float energy = cells[target.x][target.y]->Kill();
		cells[origin.x][origin.y]->GetEnergy(energy);
	}
	cells[origin.x][origin.y]->position = target;
	cells[target.x][target.y] = cells[origin.x][origin.y];
	cells[origin.x][origin.y] = NULL;
}

bool World::IsAnimal(Position pos) {
	return !(IsBlank(pos) || IsGrass(pos));
}

bool World::IsBlank(Position pos) {
	return IsBlank(pos.x, pos.y);
}

bool World::IsBlank(int x, int y) {
	return (cells[x][y] == NULL);
}

bool World::IsGrass(Position pos) {
	if (IsBlank(pos)) return false;
	return (cells[pos.x][pos.y]->type == GRASS);
}

LifeType World::GetType(int x, int y) {
	if (cells[x][y] != NULL) {
		// cout << "type: " << cells[x][y]->type << endl;
		return cells[x][y]->type;
	} else {
		return BLANK;
	}
}

LifeType World::GetType(Position pos) {
	return GetType(pos.x, pos.y);
}

float World::GetEnergy(int x, int y) {
	if (cells[x][y] != NULL) {
		// cout << "type: " << cells[x][y]->type << endl;
		return cells[x][y]->energy;
	} else {
		return 0;
	}
}
