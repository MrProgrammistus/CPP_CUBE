#pragma once
#include <glm/glm.hpp>

#define FSIZE 10

int getCellWithoutCheck(glm::ivec3 pos);
int getCell(glm::ivec3 pos);
void setCell(glm::ivec3 pos, int cell);
void swapField();