#version 330 core

in vec3 position;

layout(location = 0) out vec4 Color;
layout(location = 1) out vec4 Normal;

void main() {
	Color = vec4(0.f,0.f,1.f,0.6f);
	Normal = vec4(0.f, 0.f, 0.f, 1.f);
};