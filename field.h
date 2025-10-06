#pragma once
#include <glm/glm.hpp>

#define FSIZE 40

int getCellWithoutCheck(int x, int y, int z);
int getCell(int x, int y, int z);
void setCell(int x, int y, int z, int cell);
void swapField();
void start_field();
void stop_field();
int getCellAroundCount(int x, int y, int z, int r);