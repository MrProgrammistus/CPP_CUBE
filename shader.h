#pragma once

class Shader {
private:
	int program;

public:
	Shader(const char* path_vert, const char* path_frag);
	Shader(const char* path_vert, const char* path_geom, const char* path_frag);
	void use() const;
};

class VertexArray {
private:
	unsigned int VAO;
public:
	VertexArray(int* config, int size);
	void use() const;
};

class VertexBuffer {
private:
	unsigned int VBO;
public:
	VertexBuffer();
	void use() const;
};

class UniformBuffer {
private:
	unsigned int UBO;
public:
	UniformBuffer(int index);
	void use() const;
};

class ShaderBuffer {
private:
	unsigned int SSB;
public:
	ShaderBuffer(int index);
	void use() const;
};