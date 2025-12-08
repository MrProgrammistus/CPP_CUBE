#pragma once
#include <iostream>
#include <random>
//#include "saver.h"
#include "field.h"

#define RANDOM2D
#define ON_COLOR

std::mt19937 r{};
void life_init() {
	r.seed(std::time(0));
#ifdef GLIDER
	setCell(5, 0, 5, 1);
	setCell(5, 0, 6, 1);
	setCell(5, 0, 7, 1);
	setCell(6, 0, 7, 1);
	setCell(7, 0, 6, 1);
	//save("glider.cpp_cube_save");
#elifdef RANDOM3D
	for (int i = 0; i < FSIZE; i++) {
		for (int j = 0; j < FYSIZE; j++) {
			for (int k = 0; k < FSIZE; k++) {
				if((r() & 5) == 0) setCell(i, j, k, 1);
			}
		}
	}
#elifdef RANDOM2D
	for (int i = 0; i < FSIZE; i++) {
		for (int j = 0; j < FYSIZE; j++) {
			for (int k = 0; k < FSIZE; k++) {
				if (!(r() & 3)) setCell(i, j, k, 1);
			}
		}
	}
#endif
}

// радиатор               7-8-6-11
// мятый радиатор         8-8-6-11
// возрождение            8-8-8-26
// 
// камни                  10-12-9-26  10-14-10-26
// растущие камни         10-20-9-26 10-20-9-23 10-20-9-22
// живые камни            10-20-9-20 10-20-9-21
// мертвые камни          10-20-9-24
// мертвые растущие камни 10-20-9-25
#define A 0
#define B 0
#define C 1
#define D 6

void life_rule(int x, int y, int z, int status) {

#ifdef ON_COLOR
#ifdef RANDOM3D
	int n = getCellAroundCount(x, y, z, 1);
	if ((status == 0 && (n >= A && n <= B)) || (status != 0 && (n >= C && n <= D))) {
		int g1 = 0, g2 = 0, g3 = 0, g4 = 0;
		for (int i = -1; i < 2; i++) for (int j = -1; j < 2; j++) for (int k = -1; k < 2; k++) {
			if (getCell(x + i, y + j, z + k) == 1) g1++;
			if (getCell(x + i, y + j, z + k) == 2) g2++;
			if (getCell(x + i, y + j, z + k) == 3) g3++;
			if (getCell(x + i, y + j, z + k) == 4) g4++;
		}
		if (max(max(g1, g2), max(g3, g4)) == g1) setCell(x, y, z, 1);
		else if (max(max(g1, g2), max(g3, g4)) == g2) setCell(x, y, z, 2);
		else if (max(max(g1, g2), max(g3, g4)) == g3) setCell(x, y, z, 3);
		else if (max(max(g1, g2), max(g3, g4)) == g4) setCell(x, y, z, 4);

		if (!(r() & 63)) {
			setCell(x, y, z, 2);
		}
		else if (!(r() & 31)) {
			setCell(x, y, z, 3);
		}
		else if (!(r() & 15)) {
			setCell(x, y, z, 4);
		}
		else if (!(r() & 63)) {
			setCell(x, y, z, 1);
		}
	}
	else setCell(x, y, z, 0);
#else
	int n = getCellAroundCountIn2D(x, y, z, 1);
	if ((status == 0 && (n >= 3 && n <= 3)) || (status != 0 && (n >= 2 && n <= 3))) {
		int g1 = 0, g2 = 0, g3 = 0, g4 = 0;
		for (int i = -1; i < 2; i++) for (int j = -1; j < 2; j++) {
			if (getCell(x + i, y, z + j) == 1) g1++;
			if (getCell(x + i, y, z + j) == 2) g2++;
			if (getCell(x + i, y, z + j) == 3) g3++;
			if (getCell(x + i, y, z + j) == 4) g4++;
		}
		if (max(max(g1, g2), max(g3, g4)) == g1) setCell(x, y, z, 1);
		else if (max(max(g1, g2), max(g3, g4)) == g2) setCell(x, y, z, 2);
		else if (max(max(g1, g2), max(g3, g4)) == g3) setCell(x, y, z, 3);
		else if (max(max(g1, g2), max(g3, g4)) == g4) setCell(x, y, z, 4);

		if (!(r() & 15)) {
			setCell(x, y, z, 2);
		}
		else if (!(r() & 15)) {
			setCell(x, y, z, 3);
		}
		else if (!(r() & 15)) {
			setCell(x, y, z, 4);
		}
		else if (!(r() & 15)) {
			setCell(x, y, z, 1);
		}
	out:;
	}
	else setCell(x, y, z, 0);
#endif
#else
#ifdef RANDOM3D
	int n = getCellAroundCount(x, y, z, 1);
	if ((status == 0 && (n >= A && n <= B)) || (status != 0 && (n >= C && n <= D))) setCell(x, y, z, 1);
	else setCell(x, y, z, 0);
#else
	int n = getCellAroundCountIn2D(x, y, z, 1);
	if ((status == 0 && (n >= 3 && n <= 3)) || (status != 0 && (n >= 2 && n <= 3))) setCell(x, y, z, 1);
	else setCell(x, y, z, 0);
#endif
#endif // ON_COLOR

}