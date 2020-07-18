#version 330 core

in vec3 vertexColor;
out vec4 outColor;

void main () {
	outColor = vec4(abs(vertexColor), 1.0f);
}