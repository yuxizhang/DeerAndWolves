#ifndef DEER_H
#define DEER_H

#include <iostream>
#include <queue>

#include "debug.h"
#include "grass.h"
#include "utils.h"
#include "world.h"

using namespace std;

static const float kWalkSpeed = 1;

class Deer : public Life {
public:
	Deer(World* world, int lifespan, float max_energy, Position pos) :
		Life(DEER, world, lifespan, max_energy, pos),
		hunger(0) {

	}


	void Update() {
		Life::Update();
		cout << "deer update" << endl;
		// hunger += energy / 10;
		// movement += (movement < 10) ? 1 : 0;
		// RunAwayFromWolves(env.wolves);
		EatGrass();
	}

private:
	int movement;
	float hunger;
	bool done;


	void EatGrass() {
		Position grass_pos = FindNearest(GRASS);
		// PrintMap(world, "deer");
		if (grass_pos.IsValid()) {
			Position next_pos = FindPath(grass_pos);
			done = MoveTo(next_pos);
		}
	}

	Position FindNearest(LifeType type) {
		bool inqueue[kMapSize][kMapSize];
		memset(inqueue, false, sizeof(inqueue));
		int dx[4] = {0, 1, 0, -1};
		int dy[4] = {1, 0, -1, 0};
		queue<Position> bfs;
		bfs.push(position);
		inqueue[position.x][position.y] = true;

		// struct node {
		// 	Position pos;
		// 	int parent;
		// 	Node(Position pos, int parent) : pos(pos), parent(parent) {}
		// };
		// vector<node> path;
		// path.push_back(Node(position), 0);
		cout << world->GetType(position) << endl;
		while (!bfs.empty()) {
			Position pos = bfs.front();
			bfs.pop();
			if (world->GetType(pos) == type) {
				return pos;
			}
			for (int k = 0; k < 4; ++k) {
				Position newpos(pos.x + dx[k], pos.y + dy[k]);
				if (newpos.IsValid() && (world->GetType(pos) == BLANK)
						&& !inqueue[newpos.x][newpos.y]) {
					bfs.push(newpos);
					inqueue[newpos.x][newpos.y] = true;
				}
			}
		}
		return Position(-1, -1);
	}

	Position FindPath(const Position& target) const {
		int dirx = (target.x > position.x) ? 1 : -1;
		int diry = (target.y > position.y) ? 1 : -1;
		int dx[4] = {dirx, 0, -dirx, 0};
		int dy[4] = {0, diry, 0, -diry};
		for (int k = 0; k < 4; ++k) {
			if (world->IsBlank(position.x + dx[k], position.y + dy[k])) {
				return Position(position.x + dx[k], position.y + dy[k]);
			}
		}
		return Position(position);
	}

	bool MoveTo(const Position& target) const {
		if (target == position) return false;
		world->MoveLife(position, target);
		return true;
	}
};

#endif