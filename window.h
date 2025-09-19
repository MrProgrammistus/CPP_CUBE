#pragma once
#include <GLFW/glfw3.h>

void createWindow(int w, int h, const char* name);
void loadWindow();
void runWindow();
extern GLFWwindow* window;
extern int width, height;
extern void (*start)();
extern void (*update)(float time);