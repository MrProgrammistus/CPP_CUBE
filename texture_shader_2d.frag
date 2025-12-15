#version 450

layout(binding = 0) uniform sampler2D texture0;

out vec4 outColor;

in vec2 tex;

void main(){
	outColor = texture(texture0, tex);
}