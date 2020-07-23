#pragma once
#include <string>
#include <GL/glew.h>
#include <vector>
#include <map>
#include "GL0bShader.h"

// TODO: figure out which ones are redundant
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GL0bProgram {
public:
	GL0bProgram();
	~GL0bProgram();

	void addShader(GLenum type, const std::string& path);
	void link();
	void use();
	void dispose();
	void setUniformMat4(const char* name, const glm::mat4& matrix); // TODO: make this a template
	const unsigned int& id();
private:
	unsigned int mID;
	std::vector<GL0bShader> mShaders;
	std::map<std::string, GLuint> mUniforms; 
};