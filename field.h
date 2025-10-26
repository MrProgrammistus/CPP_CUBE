#pragma once
#include <glm/glm.hpp>

// NOTSAVE_MODE | SAVE_MODE | LOAD_MODE
#define SAVE_MODE
#define FSIZE 200
#define FYSIZE 1

int getCellWithoutCheck(int x, int y, int z);
int getInvertCellWithoutCheck(int x, int y, int z);
int getCell(int x, int y, int z);
int getCellOrZero(int x, int y, int z);
void setCell(int x, int y, int z, int cell);
void swapField();
void start_field();
void stop_field();
int getCellAroundCount(int x, int y, int z, int r);
int getCellAroundCountIn2D(int x, int y, int z, int r);