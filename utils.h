#ifndef UTILS_H
#define UTILS_H

#include <iostream>

using namespace std;

const int kMapSize = 10;

enum LifeType {
	BLANK, GRASS, DEER, WOLF
};

struct Position {
	int x;
	int y;
	Position(const Position& pos) {
		x = pos.x;
		y = pos.y;
	}
	Position(const int xx, const int yy) {
		x = xx;
		y = yy;
	}
	inline int GetKey() const {
		return x * kMapSize + y;
	}

	inline bool IsValid() const {
		return (x >= 0) && (x < kMapSize) && (y >= 0) && (y < kMapSize);
	}
};

bool operator==(const Position& lhs, const Position& rhs) {
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

#endif