#pragma once
#include <GLFW/glfw3.h>
#include <set>

void createWindow(int w, int h, const char* name);
void runWindow();
extern GLFWwindow* window;
extern int width, height;
extern void (*start)();
extern void (*update)(float time);

extern std::set<void(*)(float)> onUpdateEvent;
extern std::set<void(*)(float, float)> onResizeEvent;