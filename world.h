#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <list>
#include "utils.h"

using namespace std;

// struct CellInfo {
// 	char type;
// 	float energy;
// 	int speed;
// 	CellInfo() : type(CH_BLANK), energy(0), speed(0) {}
// };

class Life;

class World {
public:
	World();
	~World();

	void Update();

	void SetBlank(Position pos);

	void AddLife(Life* life);
	void MoveLife(Position origin, Position target);

	bool IsBlank(Position pos);
	bool IsBlank(int x, int y);

	bool IsGrass(Position pos); 

	bool IsAnimal(Position pos);
	
	LifeType GetType(int x, int y);

	LifeType GetType(Position pos);

	float GetEnergy(int x, int y);

	void PrintMap(string label = "") {
		// ofstream fout("map.txt");
		char symbol[4] = {'.', '*', 'o', 'x'};
		cout << label << endl;
		for (int i = 0; i < kMapSize; ++i) {
			for (int j = 0; j < kMapSize; ++j) {
				cout << symbol[GetType(i, j)];
			}
			cout << endl;
		}

		for (int i = 0; i < 1; ++i) cout << endl;
		// string st;
		// getline(cin, st);
	}

private:
	Life*** cells;
	list<Life*> grass_list;
	list<Life*> deer_list;

	void NewGrass();
};



#endif