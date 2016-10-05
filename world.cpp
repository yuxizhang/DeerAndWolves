#include "world.h"

#include <stdio.h>      /* NULL */
#include "life.h"
#include "grass.h"
#include "deer.h"
#include "wolf.h"

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
	wolf_list.clear();

	deer_amount = 0;
	wolf_amount = 0;
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

	cout << "**************** new round *****************\n" << endl;

	// cout << "initla map" << endl;
	// PrintMap();

	// cout << "wolf turn begin" << endl;
	UpdateGroup(wolf_list);
	// PrintMap();
	// cout << "wolf turn end" << endl;

	// cout << "deer turn begin" << endl;
	// cout << "deer amount: " << deer_list.size() << endl;
	// Update deer
	UpdateGroup(deer_list);
	// PrintMap();
	// cout << "deer turn end" << endl;

	// cout << "grass turn begin" << endl;
	NewGrass();
	// cout << "new grass generated" << endl;
	// Update grass
	UpdateGroup(grass_list);
	// PrintMap();
	// cout << "grass turn end" << endl;
	


	
	PrintMap();

	Refresh(deer_list);
	Refresh(wolf_list);
}


void World::Refresh(list<Life*> life_list) {
	list<Life*>::iterator it = life_list.begin();
	while (it != life_list.end()) {
		(*it)->moved = false;
		++it;
	}
}

void World::UpdateGroup(list<Life*> life_list) {
	list<Life*>::iterator it = life_list.begin();
	int i = 1;
	while (it != life_list.end()) {
		// cout << "No." << i << endl;
		(*it)->Update();
		if ((*it)->dead) {
			// SetBlank((*it)->position);
			// cout << "map cleared " << endl;
			// cout << (*it)->type << " is dead" << endl;
			// Life* pt = (*it);
			// cout << "pointer address " << (*it) << endl;
			// cout << "pointer address " << pt << endl;
			// delete &pt;
			// cout << "pointer freed " << endl;
			it = life_list.erase(it);
		} else {
			++it;
		}
		i++;
	}
}

void World::NewGrass() {
	int lifespan = 100;
	int max_energy = 200;
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

void World::NewAnimal(LifeType type, Position newborn) {
	int lifespane = 100;
	int max_energy = 200;
	if (type == DEER) {
		cells[newborn.x][newborn.y] = new Deer(this, lifespane, max_energy, newborn);
	} else {
		cells[newborn.x][newborn.y] = new Wolf(this, lifespane, max_energy, newborn);
	}
}

void World::SetBlank(Position pos) {
	cells[pos.x][pos.y] = NULL;
}

int World::GetId(int x, int y) {
	if (cells[x][y] != NULL) {
		if (cells[x][y]->id >= 0)
			return cells[x][y]->id + 1;
		else
			return cells[x][y]->id;
	} else {
		return 0;
	}
}

void World::AddLife(Life* life) {
	cells[life->position.x][life->position.y] = life;
	switch (life->type) {
		case GRASS :
			life->id = 0;
			grass_list.push_back(life);
			break;
		case DEER :
			deer_amount++;
			life->id = deer_amount;
			deer_list.push_back(life);
			break;
		case WOLF :
			wolf_amount++;
			life->id = -wolf_amount;
			wolf_list.push_back(life);
			break;
		default :
			break;
	}
}

void World::MoveLife(Position origin, Position target) {
	if (!IsAnimal(origin) || GetType(target) >= GetType(origin)) {
		cout << "WARNING: cannot move life at "
			 << origin.x << " " << origin.y
			 << " to " << target.x << " " << target.y << endl;
	    cout << "origin type " << GetType(origin) << endl;
	    cout << "target type " << GetType(target) << endl;
		return;
	}
	if (!IsBlank(target)) {
		float energy = cells[target.x][target.y]->Kill();
		if (GetType(origin) - GetType(target) == 1) {
			cells[origin.x][origin.y]->GainEnergy(energy);
		}
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

bool World::IsMature(Position pos) {
	cout << cells[pos.x][pos.y] << endl;
	if (!IsBlank(pos)) {
		cout << cells[pos.x][pos.y]->type << endl;
		cout << cells[pos.x][pos.y]->IsMature() << endl;
		return cells[pos.x][pos.y]->IsMature();
	} else {
		return false;
	}
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

void World::SetMoved(Position pos) {
	cells[pos.x][pos.y]->moved = true;
}
