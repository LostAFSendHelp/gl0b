#include "GL0bProgram.h"
#include "GL0bShader.h"
#include "../Renderer/GL0bRenderer.h"
#include <iostream>

GL0bProgram::GL0bProgram(): mID(glCreateProgram())
{
	std::cout << "PROGRAM CREATED: " << mID << std::endl;
}

GL0bProgram::~GL0bProgram()
{
}

void GL0bProgram::addShader(GLenum type, const std::string& path)
{
	auto shader = GL0bShader(type, path);
	glAttachShader(mID, shader.id());
	mShaders.push_back(shader);
}

void GL0bProgram::link()
{
	glLinkProgram(mID);
	auto status = gl0bGetStatus(GL_LINK_STATUS, mID);
	
	if (status != nullptr) {
		std::cout << "PROGRAM LINK ERROR [ID " << mID << "]: " << status << std::endl;
		delete[] status;
	}
	else {
		std::cout << "PROGRAM LINK SUCCESS: " << mID << std::endl;
	}

	for (const auto& shader : mShaders) {
		shader.dispose();
	}
}

void GL0bProgram::use()
{
	glUseProgram(mID);
}

void GL0bProgram::setUniformMat4(const char* name, const glm::mat4& matrix) {
	use();
	GLint location;

	if (mUniforms.find(name) == mUniforms.end()) {
		location = glGetUniformLocation(mID, name);
		if (location >= 0) mUniforms.insert({ name, location });
		else return;
	} else {
		location = mUniforms.at(name);
	}

	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void GL0bProgram::dispose()
{
	glDeleteProgram(mID);
}

const unsigned int& GL0bProgram::id()
{
	return mID;
}
