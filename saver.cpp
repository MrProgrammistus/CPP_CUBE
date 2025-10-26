#include "saver.h"
#include <fstream>
#include "field.h"
#include <Windows.h>
#include <iostream>

std::ofstream file;

std::string getTime() {
	time_t ltime;
	char buf[26];
	errno_t err;

	time(&ltime);
	ctime_s(buf, 26, &ltime);
	buf[13] = '.';
	buf[16] = '.';
	buf[24] = '\0';
	return std::string(buf);
}

void save(std::string name) {
	//CreateDirectory((const WCHAR*)(PATH), NULL);
	file.open(PATH + name);

	file << FSIZE << " " << FYSIZE << "\n";

	for (int i = 0; i < FSIZE; i++) {
		for (int j = 0; j < FYSIZE; j++) {
			for (int k = 0; k < FSIZE; k++) {
				file << (char)getInvertCellWithoutCheck(i, j, k) << " ";
			}
		}
	}
	file.close();
}

void start_save() {

	std::cout << getTime();
	file.open(PATH + getTime() + std::string(".cpp_cube_save"));

	file << FSIZE << ' ' << FYSIZE << '\n';

	for (int i = 0; i < FSIZE; i++) {
		for (int j = 0; j < FYSIZE; j++) {
			for (int k = 0; k < FSIZE; k++) {
				file << getCellWithoutCheck(i, j, k) << ' ';
			}
		}
	}
	file << '\n';
}

void add_save() {
	for (int i = 0; i < FSIZE; i++) {
		for (int j = 0; j < FYSIZE; j++) {
			for (int k = 0; k < FSIZE; k++) {
				if (getCellWithoutCheck(i, j, k) != getInvertCellWithoutCheck(i, j, k)) {
					file << i << ' ' << j << ' ' << k << ' ' << getCellWithoutCheck(i, j, k) << "    ";
				}
			}
		}
	}
	file << -1 << "\n";
}

void stop_save() {
	file.close();
}

void load(std::string name) {

}