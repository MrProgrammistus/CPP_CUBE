#include <thread>
#include "field.h"
#include <vector>
#include "render.h"
#include <Windows.h>
#include <iostream>
#include "window.h"
#include <map>
#include <set>

#define STEP_X 0.001f
#define STEP_Y 0.00005f
#define A_DELAY 20

struct LINE {
	float last_count;
	int count;
};

bool a_timer;
std::vector<float> a_data{};
int a_offset;
std::map<int, LINE> a_lines{};
bool pause, a_next_step;
void next_step() {
	a_next_step = true;
}
void pause_step() {
	pause = true;
}
void resume_step() {
	pause = false;
}

float stack_x, stack_y;
void a_func_thread() {
	while (a_timer) {
		while (pause && a_timer) {
			Sleep(20);
			if (a_next_step) {
				a_next_step = false;
				goto nf;
			}
			upload_analyzer_data(a_data.data(), a_data.size());
		}
	nf:;
		std::vector<int> counts{};
		for (int i = 0; i < FSIZE; ++i) {
			for (int j = 0; j < FYSIZE; ++j) {
				for (int k = 0; k < FSIZE; ++k) {
					if (getCell(i, j, k) != 0) {
						a_lines[getCell(i, j, k)].count++;
					}
				}
			}
		}
		for (std::pair<int, LINE> d : a_lines) {
			a_data.push_back(STEP_X * (a_offset - 1) - 1 + stack_x);
			a_data.push_back(STEP_Y * d.second.last_count - 1 + stack_y);
			a_data.push_back(reinterpret_cast<float&>(d.first));
			a_data.push_back(STEP_X * a_offset - 1 + stack_x);
			a_data.push_back(STEP_Y * d.second.count - 1 + stack_y);
			a_data.push_back(reinterpret_cast<float&>(d.first));
			a_lines[d.first].last_count = d.second.count;
			a_lines[d.first].count = 0;
		}
		a_data.push_back(STEP_X * (a_offset - 1) - 1 + stack_x);
		a_data.push_back(stack_y - 1);
		a_data.push_back(0);
		a_data.push_back(STEP_X * a_offset - 1 + stack_x);
		a_data.push_back(stack_y - 1);
		a_data.push_back(0);
		a_offset++;

		upload_analyzer_data(a_data.data(), a_data.size());
		Sleep(A_DELAY);
	}
}

std::thread a_thread;
void startAnalyzerTimer() {
	a_timer = true;
	a_thread = std::thread(a_func_thread);
}

void stopAnalyzerTimer() {
	a_timer = false;
	a_thread.join();
}

bool a_button;
bool a_action;
void mouseButtonAction(int button, int action, int mode) {
	a_button = button;
	a_action = action;
}

bool first = true;
float last_x, last_y;
void mousePosAction(float pos_x, float pos_y) {
	if (first) {
		first = 0;
	}
	else {
		if (a_action && a_button == 1) {
			float delta_x = pos_x - last_x;
			float delta_y = pos_y - last_y;
			for (int i = 0; i < a_data.size(); i+=3) {
				a_data[i] += delta_x / width * 2;
				a_data[i + 1] -= delta_y / height * 2;
			}
			stack_x += delta_x / width * 2;
			stack_y -= delta_y / height * 2;
		}
	}
	last_x = pos_x;
	last_y = pos_y;
}