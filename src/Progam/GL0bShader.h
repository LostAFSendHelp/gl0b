#pragma once
#include <string>
#include <GL/glew.h>

class GL0bShader {
public:
	GL0bShader(GLenum type, const std::string& path);
	~GL0bShader();

	const unsigned int& id();
	const std::string& source();
	void dispose() const;

private:
	unsigned int mID;
	std::string mSource;
};