#version 330 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;

uniform mat4 rotation;
uniform mat4 translation;

out vec3 vertexColor;

void main() {
	gl_Position = rotation * vec4(inPosition, 1.0f);
	gl_Position = translation * gl_Position;
	vertexColor = inColor;
}