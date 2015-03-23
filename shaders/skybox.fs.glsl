#version 330 core

in FragmentData {
	vec3 position;
	vec3 normal;
	vec2 texCoords;
} fragment;

layout(location = 0) out vec4 Color;
layout(location = 1) out vec4 Normal;

uniform sampler2D uTexture;

void main() {
	Color = vec4(texture(uTexture, fragment.texCoords).rgb,1.f); 
	Normal = vec4(vec3(fragment.normal),1.f);
};