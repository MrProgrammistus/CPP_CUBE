#pragma once
#include "field.h"
#include <iostream>

struct FB {
	unsigned char b1;
	unsigned char b2;
	unsigned char b3;
	unsigned char b4;
};

void life_init() {
	agents.push_back(glm::ivec4(FSIZE / 3 * 1, 0, FSIZE / 3 * 1, 'W'));
	agents.push_back(glm::ivec4(FSIZE / 3 * 2, 0, FSIZE / 3 * 1, 'W'));
	agents.push_back(glm::ivec4(FSIZE / 3 * 1, 0, FSIZE / 3 * 2, 'W'));
	agents.push_back(glm::ivec4(FSIZE / 3 * 2, 0, FSIZE / 3 * 2, 'W'));
}

void life_rule(int x, int y, int z, int status) {

}