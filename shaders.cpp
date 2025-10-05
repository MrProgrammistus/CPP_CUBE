#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>

#include "shader.h"

int checkShaderError(int shader, const char* name ) {
	int success;
	char log[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, 0, log);
		std::cout << "ERROR::SHADER::" << name << "::COMPILATION_FAILED\n" << log << std::endl;
	}

	return success;
}

int checkProgramError(int program) {
	int success;
	char log[512];

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, 0, log);
		std::cout << "ERROR::LINK::COMPILATION_FAILED\n" << log << std::endl;
	}

	return success;
}

int createShader(const char* path, const char* name, int program, int shaderType) {

	std::ifstream file(path);
	std::string line, text;
	while (std::getline(file, line)) text += line + '\n';
	file.close();

	int shader = glCreateShader(shaderType);
	const char* code = text.c_str();
	glShaderSource(shader, 1, &code, 0);
	glCompileShader(shader);

	checkShaderError(shader, name);

	glAttachShader(program, shader);
	glDeleteShader(shader);

	return shader;
}

Shader::Shader(const char* path_vert, const char* path_frag) {

	program = glCreateProgram();

	int vert = createShader(path_vert, "VERT", program, GL_VERTEX_SHADER);
	int frag = createShader(path_frag, "FRAG", program, GL_FRAGMENT_SHADER);

	glLinkProgram(program);

	checkProgramError(program);

	use();
}
Shader::Shader(const char* path_vert, const char* path_geom, const char* path_frag) {

	program = glCreateProgram();
	
	int vert = createShader(path_vert, "VERT", program, GL_VERTEX_SHADER);
	int geom = createShader(path_geom, "GEOM", program, GL_GEOMETRY_SHADER);
	int frag = createShader(path_frag, "FRAG", program, GL_FRAGMENT_SHADER);

	glLinkProgram(program);

	checkProgramError(program);

	use();
}

void Shader::use() const {
	glUseProgram(program);
}

VertexArray::VertexArray(int* config, int size) {
	glGenVertexArrays(1, &VAO);
	use();

	int sum = 0;
	for (int i = 0; i < size; i++) sum += config[i];

	int offset = 0;
	for (int i = 0; i < size; i++) {
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, config[i], GL_FLOAT, false, sum * sizeof(float), (void*)(offset * sizeof(float)));
		offset += config[i];
	}
}

void VertexArray::use() const {
	glBindVertexArray(VAO);
}



VertexBuffer::VertexBuffer() {
	glGenBuffers(1, &VBO);
	use();
}

void VertexBuffer::use() const {
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}


UniformBuffer::UniformBuffer(int index) {
	glGenBuffers(1, &UBO);
	glBindBufferBase(GL_UNIFORM_BUFFER, index, UBO);
	use();
}

void UniformBuffer::use() const {
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
}


ShaderBuffer::ShaderBuffer(int index) {
	glGenBuffers(1, &SSB);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, SSB);
	use();
}

void ShaderBuffer::use() const {
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSB);
}