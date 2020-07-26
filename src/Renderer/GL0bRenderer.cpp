#include "GL0bRenderer.h"
#include <string>
#include <vector>
#include <iostream>

const char* gl0bGetStatus(GLenum statusType, GLint unit) {
	int status;
	int length;
	char* target = nullptr;
	
	switch (statusType) {
	
	case GL_COMPILE_STATUS:
		
		glGetShaderiv(unit, statusType, &status);
		if (status == GL_FALSE) {

			glGetShaderiv(unit, GL_INFO_LOG_LENGTH, &length);
			target = new char[length];
			glGetShaderInfoLog(unit, sizeof(char) * length, nullptr, target);
		}
		return target;
	
	case GL_LINK_STATUS:
		glGetProgramiv(unit, statusType, &status);
		if (status == GL_FALSE) {
			glGetProgramiv(unit, GL_INFO_LOG_LENGTH, &length);
			target = new char[length];
			glGetProgramInfoLog(unit, sizeof(char) * length, nullptr, target);
		}
		return target;

	default:
		return target;
	}
}

GL0bRenderer& GL0bRenderer::shared = GL0bRenderer();

void GL0bRenderer::drawElements(const GL0bVertexArray& va, GL0bProgram& pr) {
	va.bind();
	pr.setUniformMat4("translation", va.translation());
	pr.setUniformMat4("rotation", va.rotation());
	glDrawElements(GL_TRIANGLES, va.indexBuffer().indexCount(), GL_UNSIGNED_INT, nullptr);
	va.unbind();
}

void GL0bRenderer::clear() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}