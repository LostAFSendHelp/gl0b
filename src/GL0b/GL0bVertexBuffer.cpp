#include "GL0bVertexBuffer.h"

GL0bVertexBuffer::GL0bVertexBuffer()
{
	glGenBuffers(1, &mID);
}

void GL0bVertexBuffer::bind()
{
	glBindBuffer(mType, mID);
}

void GL0bVertexBuffer::unbind()
{
	glBindBuffer(mType, 0);
}

const unsigned int& GL0bVertexBuffer::id()
{
	return mID;
}

const GLenum& GL0bVertexBuffer::type()
{
	return mType;
}
