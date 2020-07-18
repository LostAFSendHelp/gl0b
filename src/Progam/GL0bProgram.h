#pragma once
#include <string>
#include <GL/glew.h>
#include <vector>
#include "GL0bShader.h"

class GL0bProgram {
public:
	GL0bProgram();
	~GL0bProgram();

	void addShader(GLenum type, const std::string& path);
	void link();
	void use();
	void dispose();
	const unsigned int& id();
private:
	unsigned int mID;
	std::vector<GL0bShader> mShaders;
};