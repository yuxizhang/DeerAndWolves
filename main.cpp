#include <iostream>
#include <stdio.h>      /* NULL */
#include <stdlib.h>     /* srand, rand */
#include <string>
#include <time.h>       /* time */

#include "debug.h"
#include "deer.h"
#include "grass.h"
// #include "grass_group.h"
#include "life.h"
#include "utils.h"
#include "world.h"

using namespace std;

int main() {
	srand (time(NULL));

	World* world = new World();
	Deer deer(world, 200, 200, Position(0, 0));

	for (int t = 0; t < 200; ++t) {
		world->Update();
		string st;
		getline(cin, st);
	}
	
}
