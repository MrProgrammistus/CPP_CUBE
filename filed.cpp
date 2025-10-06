#include <glm/glm.hpp>
#include "field.h"
#include <thread>
#include <Windows.h>
#include <iostream>
#include "render.h"

namespace fld {
	int field[2][FSIZE][FSIZE][FSIZE]{};
	bool ifr; // index for read

	void (*game_rule)(int x, int y, int z, int status);

	void check(int& a) {
		if (a < 0) a += FSIZE;
		else if (a >= FSIZE) a -= FSIZE;
	}

	bool stop = false;
	void update_field() {
		Sleep(2000);
		while (!stop)
		{
			for (int i = 0; i < FSIZE; i++) {
				for (int j = 0; j < FSIZE; j++) {
					for (int k = 0; k < FSIZE; k++) {
						game_rule(i, j, k, fld::field[fld::ifr][i][j][k]);
					}
				}
			}
			swapField();
			Sleep(50);
		}
	}
}

int getCellWithoutCheck(int x, int y, int z) {
	return fld::field[fld::ifr][x][y][z];
}

int getCell(int x, int y, int z) {
	fld::check(x);
	fld::check(y);
	fld::check(z);
	return fld::field[fld::ifr][x][y][z];
}

void setCell(int x, int y, int z, int cell) {
	fld::check(x);
	fld::check(y);
	fld::check(z);
	fld::field[!fld::ifr][x][y][z] = cell;
}

void swapField() {
	fld::ifr = !fld::ifr;
}

int getCellAroundCount(int x, int y, int z, int r) {
	int n = 0;
	for (int i = -r; i < r + 1; i++) {
		for (int j = -r; j < r + 1; j++) {
			for (int k = -r; k < r + 1; k++) {
				if (getCell(i + x, j + y, k + z) != 0) n++;
			}
		}
	}
	if (getCell(x, y, z) != 0) n--;
	return n;
}

#include "life.h"

std::thread thread;
void start_field() {
	fld::game_rule = life_rule;
	life_init();

	swapField();
	render_field();
	thread = std::thread(fld::update_field);
}

void stop_field() {
	fld::stop = true;
	thread.join();
}