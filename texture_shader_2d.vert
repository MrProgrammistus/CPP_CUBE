#version 450

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;

out vec2 tex;

void main() {
	tex = aTex;
	gl_Position = vec4(aPos, 0.5, 1);
}