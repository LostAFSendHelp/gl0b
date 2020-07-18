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