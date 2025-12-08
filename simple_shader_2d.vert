#version 450

layout (location = 0) in vec2 aPos;
layout (location = 1) in uint aData;

out vec4 color;

void main() {

	color = vec4(0, 0, 0, 1);
	if((aData&7) == 1) color = vec4(1, 1, 1, 1);
	if((aData&7) == 2) color = vec4(1, 1, 0, 1);
	if((aData&7) == 3) color = vec4(1, 0, 1, 1);
	if((aData&7) == 4) color = vec4(0, 1, 1, 1);
	if((aData&7) == 5) color = vec4(1, 0, 0, 1);
	if((aData&7) == 6) color = vec4(0, 1, 0, 1);
	if((aData&7) == 7) color = vec4(0, 0, 1, 1);

	gl_Position = vec4(aPos, 0.5, 1);
}