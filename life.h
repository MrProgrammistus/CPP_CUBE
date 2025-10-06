#pragma once
#include "field.h"
#include <iostream>
#include <random>

#define RANDOM3D

std::mt19937 r{};
void life_init() {
	r.seed(std::time(0));
#ifdef GLIDER
	setCell(5, 0, 5, 1);
	setCell(5, 0, 6, 1);
	setCell(5, 0, 7, 1);
	setCell(6, 0, 7, 1);
	setCell(7, 0, 6, 1);
#elifdef RANDOM3D
	for (int i = 0; i < FSIZE; i++) {
		for (int j = 0; j < FSIZE; j++) {
			for (int k = 0; k < FSIZE; k++) {
				if((r() & 3) == 0) setCell(i, j, k, 1);
			}
		}
	}
#elifdef RANDOM2D
	for (int i = 0; i < FSIZE; i++) {
		for (int k = 0; k < FSIZE; k++) {
			if ((r() & 3) == 0) setCell(i, 0, k, 1);
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
#define A 10
#define B 20
#define C 9
#define D 20

void life_rule(int x, int y, int z, int status) {
#ifdef RANDOM3D
	int n = getCellAroundCount(x, y, z, 1);
	if ((status == 0 && (n >= A && n <= B)) || (status != 0 && (n >= C && n <= D))) setCell(x, y, z, 1);
	else setCell(x, y, z, 0);
#else
	if (y != 0) return;
	int n = getCellAroundCount(x, y, z, 1);
	if ((status == 0 && (n >= 3 && n <= 3)) || (status != 0 && (n >= 2 && n <= 3))) setCell(x, y, z, 1);
	else setCell(x, y, z, 0);
#endif
}