#version 330 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;

uniform mat4 transform;

out vec3 vertexColor;

void main() {
	gl_Position = transform * vec4(inPosition, 1.0f);
	vertexColor = inColor;
}