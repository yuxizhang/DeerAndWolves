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
	Deer* deer = new Deer(world, 200, 200, Position(0, 0));
	Wolf* wolf = new Wolf(world, 200, 300, Position(0, 9));

	for (int t = 0; t < 200; ++t) {
		world->Update();
		string st;
		getline(cin, st);
	}
	
}
