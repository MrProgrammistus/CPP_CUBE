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

Shader* shader_simple;
VertexBuffer* vbo_simple;
VertexArray* vao_simple;

Shader* shader_simple_2d;
VertexBuffer* vbo_simple_2d;
VertexArray* vao_simple_2d;

bool _render_timer_enable = true;
float _render_time;
void _render_timer() {
	while (_render_timer_enable)
	{
		//system("cls");
		//std::cout << 1000 / _render_time << " FPS" << std::endl;
		Sleep(1000);
	}
}

void update_render(float);
std::thread _render_timer_thread;
void start_render() {
	int config1[] = { 3, 3, 3, 3, 3, 1 };
	static Shader shader_cell = Shader("cell_shader.vert", "cell_shader.geom", "cell_shader.frag");
	static VertexBuffer vbo_cell = VertexBuffer();
	static VertexArray vao_cell = VertexArray(config1, 6);
	static UniformBuffer ubo_camera = UniformBuffer(0);
	static Camera camera{};
	::shader_cell = &shader_cell;
	::vbo_cell = &vbo_cell;
	::vao_cell = &vao_cell;
	::ubo_camera = &ubo_camera;
	::camera = &camera;

	int config2[] = { 3 };
	static Shader shader_simple = Shader("simple_shader.vert", "simple_shader.frag");
	static VertexBuffer vbo_simple = VertexBuffer();
	static VertexArray vao_simple = VertexArray(config2, 1);
	::shader_simple = &shader_simple;
	::vbo_simple = &vbo_simple;
	::vao_simple = &vao_simple;

	int config3[] = { 2 };
	static Shader shader_simple_2d = Shader("simple_shader_2d.vert", "simple_shader.frag");
	static VertexBuffer vbo_simple_2d = VertexBuffer();
	static VertexArray vao_simple_2d = VertexArray(config3, 1);
	::shader_simple_2d = &shader_simple_2d;
	::vbo_simple_2d = &vbo_simple_2d;
	::vao_simple_2d = &vao_simple_2d;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.3, 0.5, 0.7, 1);

	::camera->Start();

	onUpdateEvent.insert(update_render);

	_render_timer_thread = std::thread(_render_timer);

	float line_cube[72]{
		0, 0, 0,				FSIZE, 0, 0,
		FSIZE, 0, 0,			FSIZE, 0, FSIZE,
		FSIZE, 0, FSIZE,		0, 0, FSIZE,
		0, 0, FSIZE,			0, 0, 0,

		0, FYSIZE, 0,			FSIZE, FYSIZE, 0,
		FSIZE, FYSIZE, 0,		FSIZE, FYSIZE, FSIZE,
		FSIZE, FYSIZE, FSIZE,	0, FYSIZE, FSIZE,
		0, FYSIZE, FSIZE,		0, FYSIZE, 0,

		0, 0, 0,				0, FYSIZE, 0,
		FSIZE, 0, 0,			FSIZE, FYSIZE, 0,
		FSIZE, 0, FSIZE,		FSIZE, FYSIZE, FSIZE,
		0, 0, FSIZE,			0, FYSIZE, FSIZE,
	};

	shader_simple.use();
	vao_simple.use();
	vbo_simple.use();
	glBufferData(GL_ARRAY_BUFFER, 72 * 4, line_cube, GL_STATIC_DRAW);
}

int nm = 0;
std::vector<float> data{};
bool reload;
bool lock_render;
void render_field() {
	while (lock_render) Sleep(1);
	nm = 0;
	data.clear();
	for (int x = 0; x < FSIZE; x++) {
		for (int y = 0; y < FYSIZE; y++) {
			for (int z = 0; z < FSIZE; z++) {
				if (getCellWithoutCheck(x, y, z) != 0) {
					int _i_data = getCellWithoutCheck(x, y, z);
					float _data = reinterpret_cast<float&>(_i_data);
					std::vector<float> __data{};
					if (getCellOrZero(x + 1, y, z) == 0) { // X+
						float ___data[]{
							1 + x, 0 + y, 0 + z, 
							1 + x, 1 + y, 0 + z,
							1 + x, 0 + y, 1 + z,
							1 + x, 1 + y, 1 + z,
							1, 0, 0, _data,
						};
						__data.insert(__data.end(), ___data, std::end(___data));
						nm++;
					}
					if (getCellOrZero(x - 1, y, z) == 0) { // X-
						float ___data[]{
							0 + x, 0 + y, 0 + z,
							0 + x, 0 + y, 1 + z,
							0 + x, 1 + y, 0 + z,
							0 + x, 1 + y, 1 + z,
							-1, 0, 0, _data,
						};
						__data.insert(__data.end(), ___data, std::end(___data));
						nm++;
					}
					if (getCellOrZero(x, y + 1, z) == 0) { // Y+
						float ___data[]{
							0 + x, 1 + y, 0 + z,
							0 + x, 1 + y, 1 + z,
							1 + x, 1 + y, 0 + z,
							1 + x, 1 + y, 1 + z,
							0, 1, 0, _data,
						};
						__data.insert(__data.end(), ___data, std::end(___data));
						nm++;
					}
					if (getCellOrZero(x, y - 1, z) == 0) { // Y-
						float ___data[]{
							0 + x, 0 + y, 0 + z,
							1 + x, 0 + y, 0 + z,
							0 + x, 0 + y, 1 + z,
							1 + x, 0 + y, 1 + z,
							0, -1, 0, _data,
						};
						__data.insert(__data.end(), ___data, std::end(___data));
						nm++;
					}
					if (getCellOrZero(x, y, z + 1) == 0) { // Z+
						float ___data[]{
							0 + x, 0 + y, 1 + z,
							1 + x, 0 + y, 1 + z,
							0 + x, 1 + y, 1 + z,
							1 + x, 1 + y, 1 + z,
							0, 0, 1, _data,
						};
						__data.insert(__data.end(), ___data, std::end(___data));
						nm++;
					}
					if (getCellOrZero(x, y, z - 1) == 0) { // Z-
						float ___data[]{
							0 + x, 0 + y, 0 + z,
							0 + x, 1 + y, 0 + z,
							1 + x, 0 + y, 0 + z,
							1 + x, 1 + y, 0 + z,
							0, 0, -1, _data,
						};
						__data.insert(__data.end(), ___data, std::end(___data));
						nm++;
					}
					data.insert(data.end(), __data.begin(), __data.end());
				}
			}
		}
	}
	reload = true;
}
int nmm;
void load_data_to_gpu() {
	shader_cell->use();
	vao_cell->use();
	vbo_cell->use();
	lock_render = true; // запретить обновлять вершины
	if (reload) {
		glBufferData(GL_ARRAY_BUFFER, data.size() * 4, data.data(), GL_DYNAMIC_DRAW);
		nmm = nm;
		reload = false;
	}
	glDrawArrays(GL_POINTS, 0, nmm);
	lock_render = false; // разрешить обновлять вершины

	shader_simple->use();
	vao_simple->use();
	vbo_simple->use();
	glDrawArrays(GL_LINES, 0, 72 / 3);
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

	load_data_to_gpu();

	_render_time = time;
}

void stop_render() {
	_render_timer_enable = false;
	_render_timer_thread.join();
}