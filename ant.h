#pragma once
#include "field.h"

void life_init() {
	agents.push_back(glm::ivec4(FSIZE / 2, 0, FSIZE / 2, 'W'));
}

void life_rule(int x, int y, int z, int status) {
	int i = getAgent(x, y, z);
	if (status == 0) {
		setCell(x, y, z, 1);
		if (agents[i].w == 'W') {
			setAgent(i, --x, y, z, 'A');
			//agents[i].w = 'A';
			//agents[i].x--;
		}
		else if (agents[i].w == 'A') {
			setAgent(i, x, y, --z, 'S');
			//agents[i].w = 'S';
			//agents[i].z--;
		}
		else if (agents[i].w == 'S') {
			setAgent(i, ++x, y, z, 'D');
			//agents[i].w = 'D';
			//agents[i].x++;
		}
		else if (agents[i].w == 'D') {
			setAgent(i, x, y, ++z, 'W');
			//agents[i].w = 'W';
			//agents[i].z++;
		}
	}
	else {
		setCell(x, y, z, 0);
		if (agents[i].w == 'W') {
			setAgent(i, ++x, y, z, 'D');
			//agents[i].w = 'D';
			//agents[i].x++;
		}
		else if (agents[i].w == 'A') {
			setAgent(i, x, y, ++z, 'W');
			//agents[i].w = 'W';
			//agents[i].z++;
		}
		else if (agents[i].w == 'S') {
			setAgent(i, --x, y, z, 'A');
			//agents[i].w = 'A';
			//agents[i].x--;
		}
		else if (agents[i].w == 'D') {
			setAgent(i, x, y, --z, 'S');
			//agents[i].w = 'S';
			//agents[i].z--;
		}
	}
}