#include "saver.h"
#include <fstream>
#include <iostream>
#include "field.h"
#include "interface.h"

std::ifstream file;

void load() {
	file.open(std::string() + PATH + FILENAME);
	int fsize, fysize;
	file >> fsize >> fysize;
	if (fsize != FSIZE || fysize != FYSIZE) {
		file.close();
		std::cout << "–азмеры полей не совпадают; выставите FSIZE = " << fsize << " FYSIZE = " << fysize;
		throw 0;
	}
}
int getNextInt() {
	int a;
	file >> a;
	return a;
}
bool getNextPosedInt(int& x, int& y, int& z, int& c) {
	if (!file.is_open()) return false;
	if (file.eof()) {
		file.close();
		return false;
	}
	file >> x;
	if (x == -1) return false;
	file >> y >> z >> c;
	return true;
}