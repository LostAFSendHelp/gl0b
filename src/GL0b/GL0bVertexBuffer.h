#pragma once
#include <GL/glew.h>

#define GL0B_INDEX_POSITION 0
#define GL0B_INDEX_COLOR 1

class GL0bVertexBuffer {
public:
	GL0bVertexBuffer();
	virtual ~GL0bVertexBuffer() { }

	void bind();
	void unbind();
	virtual void update() = 0;

	const unsigned int& id();
	const GLenum& type();

protected:
	unsigned int mID;
	GLenum mType;
};