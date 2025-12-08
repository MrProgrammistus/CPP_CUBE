#version 450

out vec4 outColor;

in vec4 color;

void main(){
	outColor = vec4(color);
}