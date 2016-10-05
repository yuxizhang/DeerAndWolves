#include <iostream>
#include <stdio.h>      /* NULL */
#include <stdlib.h>     /* srand, rand */
#include <string>
#include <time.h>       /* time */

#include "animal.h"
#include "debug.h"
#include "deer.h"
#include "grass.h"
#include "life.h"
#include "utils.h"
#include "wolf.h"
#include "world.h"

using namespace std;

int main() {
	srand (time(NULL));

	World* world = new World();

	// Init
	int deer_amount = 10;
	int wolf_amount = 2;
	for (int t = 0; t < 40; ++t) {
		world->Update();
	}

	for (int i = 0; i < deer_amount; ++i) {
		int lifespan = 100 + rand() % 50 - 25;
		int max_energy = 200 + rand() % 50 - 25;
		int max_try = 10;
		int x = rand() % kMapSize, y = rand() % kMapSize;
		while (!world->IsBlank(x, y) && max_try > 0) {
			x = rand() % kMapSize;
			y = rand() % kMapSize;
			--max_try;
		}
		if (max_try > 0) new Deer(world, lifespan, max_energy, Position(x, y));
	}

	for (int t = 0; t < 20; ++t) {
		world->Update();
	}

	for (int i = 0; i < wolf_amount; ++i) {
		int lifespan = 50 + rand() % 50 - 25;
		int max_energy = 300 + rand() % 50 - 25;
		int max_try = 10;
		int x = rand() % kMapSize, y = rand() % kMapSize;
		while (!world->IsBlank(x, y) && max_try > 0) {
			x = rand() % kMapSize;
			y = rand() % kMapSize;
			--max_try;
		}
		if (max_try > 0) new Wolf(world, lifespan, max_energy, Position(x, y));
	}
	


	for (int t = 0; t < 200; ++t) {
		world->Update();
		string st;
		getline(cin, st);
	}
	
}
