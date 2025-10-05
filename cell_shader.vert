#version 450

layout (location = 0) in vec3 aPos1;
layout (location = 1) in vec3 aPos2;
layout (location = 2) in vec3 aPos3;
layout (location = 3) in vec3 aPos4;
layout (location = 4) in vec3 aNorm;
layout (location = 5) in uint aData;

out vec3 _pos1;
out vec3 _pos2;
out vec3 _pos3;
out vec3 _pos4;
out vec3 _norm;
out uint _data;

void main() {
	_pos1 = aPos1;
	_pos2 = aPos2;
	_pos3 = aPos3;
	_pos4 = aPos4;
	_norm = aNorm;
	_data = aData;
}