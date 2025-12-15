#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "window.h"
#include "render.h"
#include "field.h"
#include "analyzer.h"

int main() {
	setlocale(LC_ALL, "");
	createWindow(192*5, 108*5, "Window");;

	start_render();
	start_field();
	startAnalyzerTimer();
	runWindow();
	stop_render();
	stop_field();
	stopAnalyzerTimer();
	return 0;
}