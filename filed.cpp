#include <glm/glm.hpp>
#include "field.h"
#include <thread>
#include <Windows.h>
#include <iostream>
#include "render.h"
#include "saver.h"
#include "loader.h"
#include <time.h>

// применяемые правила
#include "ant.h"


std::vector<glm::ivec4> agents{};
std::vector<glm::ivec4> agents_buff{};

namespace fld {
	int field[2][FSIZE][FYSIZE][FSIZE]{};
	bool ifr; // index for read

	void (*game_rule)(int x, int y, int z, int status);

	void check(int& a) {
		if (a < 0) a += FSIZE;
		else if (a >= FSIZE) a -= FSIZE;
	}
	void checkY(int& a) {
		if (a < 0) a += FYSIZE;
		else if (a >= FYSIZE) a -= FYSIZE;
	}

	bool stop;
	void update_field_thread() {
		Sleep(2000);
#ifdef LOAD_MODE
		while (!stop)
		{
			int x, y, z, c;
			while (getNextPosedInt(x, y, z, c)) {
				fld::field[0][x][y][z] = fld::field[1][x][y][z] = c;
			}
			swapField();
			Sleep(DELAY);
		}
#else // not LOAD_MODE
#ifdef SAVE_MODE
		start_save();
#endif // SAVE_MODE
		while (!stop)
		{
#ifdef SAVE_MODE
			add_save();
#endif // SAVE_MODE
#ifdef CELL_MODE
			for (int i = 0; i < FSIZE; i++) {
				for (int j = 0; j < FYSIZE; j++) {
					for (int k = 0; k < FSIZE; k++) {
						game_rule(i, j, k, fld::field[fld::ifr][i][j][k]);
					}
				}
			}
			Sleep(DELAY);
#else // not CELL_MODE
			for (int i = 0; i < FSIZE; i++) {
				for (int j = 0; j < FYSIZE; j++) {
					for (int k = 0; k < FSIZE; k++) {
						setCell(i, j, k, getCell(i, j, k));
					}
				}
			}
			agents_buff = std::vector<glm::ivec4>(agents);
			for (int i = 0; i < agents_buff.size(); ++i) {
				int x = agents_buff[i].x, y = agents_buff[i].y, z = agents_buff[i].z;
				game_rule(x, y, z, fld::field[fld::ifr][x][y][z]);
			}
			Sleep(DELAY);
#endif
			swapField();
		}
#ifdef SAVE_MODE
			stop_save();
#endif // SAVE_MODE
#endif // LOAD_MODE
	}
	void render_field_thread() {
		Sleep(2000);
		while (!stop)
		{
			Sleep(50);
			render_field();
		}
	}
}

int getAgent(int x, int y, int z) {
	for (int i = 0; i < agents.size(); ++i) if (agents[i].x == x && agents[i].y == y && agents[i].z == z) return i;
	return -1;
}
void setAgent(int i, int x, int y, int z, int w) {
	fld::check(x);
	fld::checkY(y);
	fld::check(z);
	agents[i] = glm::vec4(x, y, z, w);
}

int getCellWithoutCheck(int x, int y, int z) {
	return fld::field[fld::ifr][x][y][z];
}
int getInvertCellWithoutCheck(int x, int y, int z) {
	return fld::field[!fld::ifr][x][y][z];
}

int getCell(int x, int y, int z) {
	fld::check(x);
	fld::checkY(y);
	fld::check(z);
	return fld::field[fld::ifr][x][y][z];
}

int getCellOrZero(int x, int y, int z) {
	if (x < 0 || y < 0 || z < 0 || x >= FSIZE || y >= FYSIZE || z >= FSIZE) return 0;
	return fld::field[fld::ifr][x][y][z];
}

void setCell(int x, int y, int z, int cell) {
	fld::check(x);
	fld::checkY(y);
	fld::check(z);
	fld::field[!fld::ifr][x][y][z] = cell;
}
void set2Cell(int x, int y, int z, int cell) {
	fld::check(x);
	fld::checkY(y);
	fld::check(z);
	fld::field[fld::ifr][x][y][z] = cell;
	fld::field[!fld::ifr][x][y][z] = cell;
}

void setCellWithoutCheck(int x, int y, int z, int cell) {
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
int getCellAroundCountIn2D(int x, int y, int z, int r) {
	int n = 0;
	for (int i = -r; i < r + 1; i++) {
		for (int k = -r; k < r + 1; k++) {
			if (getCell(i + x, y, k + z) != 0) n++;
		}
	}
	if (getCell(x, y, z) != 0) n--;
	return n;
}

std::thread thread;
std::thread render_thread;
void start_field() {
	fld::stop = false;
	agents.clear();
#ifdef LOAD_MODE
	load();
	for (int i = 0; i < FSIZE; i++) {
		for (int j = 0; j < FYSIZE; j++) {
			for (int k = 0; k < FSIZE; k++) {
				fld::field[0][i][j][k] = fld::field[1][i][j][k] = getNextInt();
			}
		}
	}
#else
	for (int i = 0; i < FSIZE; i++) {
		for (int j = 0; j < FYSIZE; j++) {
			for (int k = 0; k < FSIZE; k++) {
				fld::field[0][i][j][k] = 0;
				fld::field[1][i][j][k] = 0;
			}
		}
	}
	fld::game_rule = life_rule;
	life_init();
#endif

	swapField();
	render_field();
	thread = std::thread(fld::update_field_thread);
	render_thread = std::thread(fld::render_field_thread);
}

void stop_field() {
	fld::stop = true;
	thread.join();
	render_thread.join();
}