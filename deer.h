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
		path.clear();
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
	struct Node {
		Position pos;
		int parent;
		Node(Position pos, int parent) : pos(pos), parent(parent) {}
	};
	int movement;
	float hunger;
	bool done;
	vector<Position> path;

	void EatGrass() {
		Position grass_pos = FindNearest(GRASS);
		cout << "grass pos: " << grass_pos.x << " " << grass_pos.y << endl;
		// PrintMap(world, "deer");
		if (grass_pos.IsValid()) {
			Position next_pos = FindPath(grass_pos);
			cout << "next step: " << next_pos.x << " " << next_pos.y << endl;
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

		path.clear();

		vector<Node> path_queue;
		int path_index = 0;
		path_queue.push_back(Node(position, path_index));

		cout << world->GetType(position) << endl;
		while (!bfs.empty()) {
			Position pos = bfs.front();
			bfs.pop();
			for (int k = 0; k < 4; ++k) {
				Position newpos(pos.x + dx[k], pos.y + dy[k]);
				if (newpos.IsValid()) {
					if (world->GetType(newpos) == type) {
						path_queue.push_back(Node(newpos, path_index));
						int i = path_queue.size() - 1;
						while (i > 0) {
							path.push_back(path_queue[i].pos);
							i = path_queue[i].parent;
						}
						return newpos;
					}
					if (!inqueue[newpos.x][newpos.y]
							&& (world->GetType(newpos) == BLANK)) {
						bfs.push(newpos);
						path_queue.push_back(Node(newpos, path_index));
						inqueue[newpos.x][newpos.y] = true;
					}
				}
			}
			++path_index;
		}
		
		return Position(-1, -1);
	}

	Position FindPath(const Position& target) {
		if (path.empty()) return Position(-1, -1);
		Position ret = path.back();
		path.pop_back();
		return ret;
		// return Position(-1, -1);
	}

	bool MoveTo(const Position& target) const {
		if (position.IsSame(target)) return false;
		world->MoveLife(position, target);
		return true;
	}
};

#endif