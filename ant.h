#pragma once
#include "field.h"

void life_init() {
	agents.push_back(glm::ivec4(FSIZE / 2, 0, FSIZE / 2, 'W'));
}

void life_rule(int x, int y, int z, int status) {
	int i = getAgent(x, y, z);
	if (status == 0) {
		set2Cell(x, y, z, 1);
		if (agents[i].w == 'W') {
			agents[i].w = 'A';
			agents[i].x--;
		}
		else if (agents[i].w == 'A') {
			agents[i].w = 'S';
			agents[i].z--;
		}
		else if (agents[i].w == 'S') {
			agents[i].w = 'D';
			agents[i].x++;
		}
		else if (agents[i].w == 'D') {
			agents[i].w = 'W';
			agents[i].z++;
		}
	}
	else {
		set2Cell(x, y, z, 0);
		if (agents[i].w == 'W') {
			agents[i].w = 'D';
			agents[i].x++;
		}
		else if (agents[i].w == 'A') {
			agents[i].w = 'W';
			agents[i].z++;
		}
		else if (agents[i].w == 'S') {
			agents[i].w = 'A';
			agents[i].x--;
		}
		else if (agents[i].w == 'D') {
			agents[i].w = 'S';
			agents[i].z--;
		}
	}
}