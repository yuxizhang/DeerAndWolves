#include "animal.h"

#include <iostream>
#include <queue>

using namespace std;

static const float kMoveStrength = 10;
static const float kHungerSpeed = 0.1;
static const float kHungerLevel = 0.2;


Animal::Animal(LifeType type, World* world, int lifespan, float max_energy, Position pos) :
	Life(type, world, lifespan, max_energy, pos),
	strength(0) {
	path.clear();
}

Animal::~Animal() {
	path.clear();
}

void Animal::Update() {
	Life::Update();
	cout << "deer update" << endl;
	hunger += energy * kHungerSpeed;
	strength = Max(strength + energy - hunger, energy);
	// movement += (movement < 10) ? 1 : 0;
	// RunAwayFromWolves(env.wolves);
	
}

void Animal::GetEnergy(float energy) {
	hunger -= energy;
}

void Animal::FindFood(LifeType type) {
	// bool hungry = hunger > energy * kHungerLevel;
	if (hunger < 0) return;
	Position target_pos = FindNearest(type);
	// cout << "grass pos: " << grass_pos.x << " " << grass_pos.y << endl;

	if (target_pos.IsValid()) {
		while (strength > kMoveStrength) {
			Position next_pos = FindPath(target_pos);
			// cout << "next step: " << next_pos.x << " " << next_pos.y << endl;
			if (!MoveTo(next_pos)) break;
		}
	}
}

Position Animal::FindNearest(LifeType type) {
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

Position Animal::FindPath(const Position& target) {
	if (path.empty()) return Position(-1, -1);
	Position ret = path.back();
	path.pop_back();
	return ret;
}

bool Animal::MoveTo(const Position& target) {
	if (!target.IsValid()) return false;
	if (position.IsSame(target)) return false;
	world->MoveLife(position, target);
	strength -= kMoveStrength;
	return true;
}