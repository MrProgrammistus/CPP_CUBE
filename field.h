#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "interface.h"

extern std::vector<glm::ivec4> agents;
int getAgent(int x, int y, int z);
void setAgent(int i, int x, int y, int z, int w);

int getCellWithoutCheck(int x, int y, int z);
int getInvertCellWithoutCheck(int x, int y, int z);
int getCell(int x, int y, int z);
int getCellOrZero(int x, int y, int z);
void setCell(int x, int y, int z, int cell);
void set2Cell(int x, int y, int z, int cell);
void setCellWithoutCheck(int x, int y, int z, int cell);
int getCellAroundCount(int x, int y, int z, int r);
int getCellAroundCountIn2D(int x, int y, int z, int r);
void swapField();
void start_field();
void stop_field();
void pause_field();
void resume_field();
void next_frame();

extern int step;