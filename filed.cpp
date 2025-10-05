#include <glm/glm.hpp>
#include "field.h"

namespace fld {
	int field[2][FSIZE][FSIZE][FSIZE]{};
	bool ifr; // index for read

	void check(int& a) {
		if (a < 0) a += FSIZE;
		else if (a >= FSIZE) a -= FSIZE;
	}
}

int getCellWithoutCheck(glm::ivec3 pos) {
	return fld::field[fld::ifr][pos.x][pos.y][pos.z];
}

int getCell(glm::ivec3 pos) {
	int x = pos.x, y = pos.y, z = pos.z;
	fld::check(x);
	fld::check(y);
	fld::check(z);
	return fld::field[fld::ifr][x][y][z];
}

void setCell(glm::ivec3 pos, int cell) {
	int x = pos.x, y = pos.y, z = pos.z;
	fld::check(x);
	fld::check(y);
	fld::check(z);
	fld::field[!fld::ifr][x][y][z] = cell;
}

void swapField() {
	fld::ifr = !fld::ifr;
}