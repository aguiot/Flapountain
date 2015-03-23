#version 330 core

layout(location = 0) in vec3 aVertexPosition;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out	vec3 position;

void main() {
    vec4 vertexPosition = vec4(aVertexPosition, 1);
    position = aVertexPosition;
    //gl_PointSize = 50;
	gl_Position = uMVPMatrix*vertexPosition;
}