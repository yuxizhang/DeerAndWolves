#include "utils.h"

int GetSign(int x) {
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}

float Max(float x, float y) {
	if (x > y) return x; else return y;
}