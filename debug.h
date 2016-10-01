#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <fstream>
#include <string>
#include "world.h"

void PrintMap(World* world, string label = "") {
	// ofstream fout("map.txt");
	char symbol[4] = {'.', '*', 'o', 'x'};
	cout << label << endl;
	for (int i = 0; i < kMapSize; ++i) {
		for (int j = 0; j < kMapSize; ++j) {
			cout << symbol[world->GetType(i, j)];
		}
		cout << endl;
	}

	for (int i = 0; i < 1; ++i) cout << endl;
	// string st;
	// getline(cin, st);
}

#endif