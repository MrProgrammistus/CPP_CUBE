#version 450

out vec4 outColor;

in vec3 pos;
in vec3 norm;
in vec4 color;
in flat uint data;

void main(){
	outColor = color;
}