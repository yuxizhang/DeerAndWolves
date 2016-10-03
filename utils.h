#ifndef UTILS_H
#define UTILS_H

#include <iostream>

using namespace std;

const int kMapSize = 10;

enum LifeType {
	BLANK, GRASS, DEER, WOLF
};

int GetSign(int x);

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

	bool IsSame(const Position& pos) const {
		return (x == pos.x && y == pos.y);
	}
};


// bool operator==(const Position& lhs, const Position& rhs) {
// 	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
// }

// bool operator!=(const Position& lhs, const Position& rhs) {
// 	return !(lhs == rhs);
// }

#endif