#ifndef GRASS_GROUP_H
#define GRASS_GROUP_H

#include <stdlib.h>
#include <unordered_map>
#include <vector>
#include "grass.h"
#include "utils.h"
#include "world_map.h"

using namespace std;

class GrassGroup {
public:
	GrassGroup(WorldMap* map) : world_map(map) {
		grasses.clear();
	}

	void Update() {
		for (int i = 0; i < grasses.size(); ++i) {
			grasses[i].Update();
			if (grasses[i].dead) {
				world_map->SetBlank(grasses[i].position);
				grasses.erase(grasses.begin() + i);
				--i;
			} else {
				// world_map->SetGrass(grasses[i]);
			}
		}
	}

	void NewGrass() {
		int lifespan = 100;
		int max_energy = 100;
		int max_try = 10;
		Position pos(rand() % kMapSize, rand() % kMapSize);
		while (!world_map->IsBlank(pos) && max_try > 0) {
			pos.x = rand() % kMapSize;
			pos.y = rand() % kMapSize;
			--max_try;
		}
		if (max_try == 0) return;
		Grass new_grass(world_map, lifespan, max_energy, pos);
		cout << "Grass type: " << new_grass.type << endl;
		grasses.push_back(new_grass);
		// world_map->SetLife(new_grass);
	}

	int GetSize() const {
		return grasses.size();
	}

	Grass operator[](const int i) {
		return grasses[i];
	}

private:
	WorldMap* world_map;

	vector<Grass> grasses;
};

#endif