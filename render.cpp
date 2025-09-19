#include <GL/glew.h>
#include <windows.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#include "render.h"
#include "shader.h"
#include "camera.h"
#include "window.h"

Shader* shader_cell;
VertexBuffer* vbo_cell;
VertexArray* vao_cell;
UniformBuffer* ubo_camera;
Camera* camera;

float vertices[] = {
	0, 0, 0,
	1, 0, 0,
	1, 1, 0
};

float _render_time;
void timer(HWND, UINT, UINT_PTR, DWORD) {
	system("cls");
	std::cout << 1000 / _render_time << " FPS" << std::endl;
}

void start_triangle() {
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void start_render() {
	int config[] = { 3 };
	static Shader shader_cell = Shader("cell_shader.vert", "cell_shader.frag");
	static VertexBuffer vbo_cell = VertexBuffer();
	static VertexArray vao_cell = VertexArray(config, 1);
	static UniformBuffer ubo_camera = UniformBuffer(0);
	static Camera camera{};
	::shader_cell = &shader_cell;
	::vbo_cell = &vbo_cell;
	::vao_cell = &vao_cell;
	::ubo_camera = &ubo_camera;
	::camera = &camera;

	glClearColor(0.3, 0.5, 0.7, 1);

	start_triangle();
	::camera->Start();

	SetTimer(0, 0, 1000, timer);
}

void update_triangle() {
	shader_cell->use();
	vao_cell->use();
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void update_render(float time) {
	ubo_camera->use();
	glm::mat4 view = camera->GetView();
	glBufferData(GL_UNIFORM_BUFFER, sizeof(view), &view, GL_STREAM_DRAW);
	camera->Update(time);
	update_triangle();

	_render_time = time;
}