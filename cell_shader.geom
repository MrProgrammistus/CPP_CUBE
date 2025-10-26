#version 450

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

layout(std140, binding = 0) uniform camera {
	mat4 view;
	vec3 player;
};

in vec3 _pos1[1];
in vec3 _pos2[1];
in vec3 _pos3[1];
in vec3 _pos4[1];
in vec3 _norm[1];
in uint _data[1];

out vec3 pos;
out vec3 norm;
out vec4 color;
out flat uint data;

void light() {
	vec3 to_player = normalize(player - pos);
	float angle = max(dot(norm, to_player), 0);
	//float angle = 1;
	color = vec4(0.4, 0.5, 0.7, 1);
	color.xyz *= angle;
}

void main() {
	norm = _norm[0];
	data = _data[0];


	
	pos = _pos1[0];
	light();
	gl_Position = view * vec4(pos, 1);
	EmitVertex();


	
	pos = _pos2[0];
	light();
	gl_Position = view * vec4(pos, 1);
	EmitVertex();


	
	pos = _pos3[0];
	light();
	gl_Position = view * vec4(pos, 1);
	EmitVertex();


	
	pos = _pos4[0];
	light();
	gl_Position = view * vec4(pos, 1);
	EmitVertex();



	EndPrimitive();
}