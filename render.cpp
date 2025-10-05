#include <GL/glew.h>
#include <windows.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <thread>
#include <vector>

#include "render.h"
#include "shader.h"
#include "camera.h"
#include "window.h"
#include "field.h"

Shader* shader_cell;
VertexBuffer* vbo_cell;
VertexArray* vao_cell;
UniformBuffer* ubo_camera;
Camera* camera;

bool _render_timer_enable = true;
float _render_time;
void _render_timer() {
	while (_render_timer_enable)
	{
		system("cls");
		std::cout << 1000 / _render_time << " FPS" << std::endl;
		Sleep(1000);
	}
}

void update_render(float);
std::thread _render_timer_thread;
void start_render() {
	int config[] = { 3, 3, 3, 3, 3, 1 };
	static Shader shader_cell = Shader("cell_shader.vert", "cell_shader.geom", "cell_shader.frag");
	static VertexBuffer vbo_cell = VertexBuffer();
	static VertexArray vao_cell = VertexArray(config, 6);
	static UniformBuffer ubo_camera = UniformBuffer(0);
	static Camera camera{};
	::shader_cell = &shader_cell;
	::vbo_cell = &vbo_cell;
	::vao_cell = &vao_cell;
	::ubo_camera = &ubo_camera;
	::camera = &camera;

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.3, 0.5, 0.7, 1);

	::camera->Start();

	onUpdateEvent.insert(update_render);

	_render_timer_thread = std::thread(_render_timer);

	setCell(glm::ivec3{ 1, 1, 1 }, 1);
	setCell(glm::ivec3{ 0, 0, 0 }, 1);
	swapField();
	setCell(glm::ivec3{ 1, 1, 1 }, 1);
	setCell(glm::ivec3{ 0, 0, 0 }, 1);
}

void update_field() {
	swapField();
	int n = 0;
	std::vector<float> data{};
	for (int x = 0; x < FSIZE; x++) {
		for (int y = 0; y < FSIZE; y++) {
			for (int z = 0; z < FSIZE; z++) {
				if (getCellWithoutCheck(glm::ivec3{x, y, z})) {
					unsigned _data = 0;
					float __data[]{
						1 + x, 0 + y, 0 + z,
						1 + x, 1 + y, 0 + z,
						1 + x, 0 + y, 1 + z,
						1 + x, 1 + y, 1 + z,
						1, 0, 0, _data,
						0 + x, 0 + y, 0 + z,
						0 + x, 0 + y, 1 + z,
						0 + x, 1 + y, 0 + z,
						0 + x, 1 + y, 1 + z,
						-1, 0, 0, _data,
						0 + x, 1 + y, 0 + z,
						0 + x, 1 + y, 1 + z,
						1 + x, 1 + y, 0 + z,
						1 + x, 1 + y, 1 + z,
						0, 1, 0, _data,
						0 + x, 0 + y, 0 + z,
						1 + x, 0 + y, 0 + z,
						0 + x, 0 + y, 1 + z,
						1 + x, 0 + y, 1 + z,
						0, -1, 0, _data,
						0 + x, 0 + y, 1 + z,
						1 + x, 0 + y, 1 + z,
						0 + x, 1 + y, 1 + z,
						1 + x, 1 + y, 1 + z,
						0, 0, 1, _data,
						0 + x, 0 + y, 0 + z,
						0 + x, 1 + y, 0 + z,
						1 + x, 0 + y, 0 + z,
						1 + x, 1 + y, 0 + z,
						0, 0, -1, _data,
					};
					data.insert(data.end(), __data, std::end(__data));
					n++;
				}
			}
		}
	}
	shader_cell->use();
	vao_cell->use();
	vbo_cell->use();
	glBufferData(GL_ARRAY_BUFFER, data.size() * 4, data.data(), GL_STREAM_DRAW);
	glDrawArrays(GL_POINTS, 0, n * 6);
}

struct UBO_CAMERA_DATA {
	glm::mat4 view;
	glm::vec3 pos;
};
void update_render(float time) {
	ubo_camera->use();
	glm::mat4 view = camera->GetView();
	glm::vec3 pos = camera->GetPos();
	UBO_CAMERA_DATA data{view, pos};
	glBufferData(GL_UNIFORM_BUFFER, sizeof(data), &data, GL_STREAM_DRAW);
	camera->Update(time);

	update_field();

	_render_time = time;
}

void stop_render() {
	_render_timer_enable = false;
	_render_timer_thread.join();
}