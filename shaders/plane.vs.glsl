#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoords;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out FragmentData {
	vec3 position;
	vec3 normal;
	vec2 texCoords;
} fragment;

void main() {
    vec4 vertexPosition = vec4(aVertexPosition, 1);
    vec4 vertexNormal = vec4(aVertexNormal, 0);

    // fragment.position = vec3(uMVMatrix * vertexPosition);
    fragment.position = aVertexPosition;
    // fragment.normal = vec3(uNormalMatrix * vertexNormal);
    fragment.normal = aVertexNormal;
	fragment.texCoords = aVertexTexCoords;

	gl_Position = uMVPMatrix*vertexPosition;
}