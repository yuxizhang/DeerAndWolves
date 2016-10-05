#include "animal.h"

#include <iostream>
#include <queue>

using namespace std;

struct Node {
	Position pos;
	int parent;
	Node(Position pos, int parent) : pos(pos), parent(parent) {}
};


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
	hunger += energy * kHungerSpeed;
	strength = Max(strength + energy - hunger, energy);
	if (hunger > energy) {
		Life::KillSelf();
		return;
	}
}

void Animal::GainEnergy(float energy) {
	hunger -= energy;
}

bool Animal::FindFood(LifeType type) {
	if (hunger < 0) return false;
	bool move = false;
	Position target_pos = FindNearest(type);

	if (target_pos.IsValid()) {
		while (strength > kMoveStrength) {
			Position next_pos = FindPath(target_pos);
			if (!MoveTo(next_pos)) break; else move = true;
		}
	}
	return move;
}

bool Animal::FindMate() {
	bool move = false;
	Position target_pos = FindNearest(type);
	if (target_pos.IsValid()) {
		path.erase(path.begin());
		while (strength > kMoveStrength) {
			Position next_pos = FindPath(target_pos);
			if (!MoveTo(next_pos)) break; else move = true;
		}
		if (position.Dist(target_pos) == 1) {
			world->SetMoved(target_pos);
			Position newborn_pos = FindNearest(BLANK);
			if (newborn_pos.IsValid()) world->NewAnimal(type, newborn_pos);
		}
	}
	return move;
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
			if (newpos.IsValid() && !position.IsSame(newpos)) {
				if (world->GetType(newpos) == type
						&& (type != this->type || world->IsMature(newpos))) {
					path_queue.push_back(Node(newpos, path_index));
					int i = path_queue.size() - 1;
					while (i > 0) {
						path.push_back(path_queue[i].pos);
						i = path_queue[i].parent;
					}
					return newpos;
				}
				if (!inqueue[newpos.x][newpos.y]
						&& (world->GetType(newpos) < this->type)) {
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