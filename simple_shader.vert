#version 450

layout (location = 0) in vec3 aPos;

layout(std140, binding = 0) uniform camera {
	mat4 view;
	vec3 player;
};

void main() {
	gl_Position = view * vec4(aPos, 1);
}