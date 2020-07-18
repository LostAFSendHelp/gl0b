#include <GL/glew.h>
#include "GL0bIndexBuffer.h"

GL0bIndexBuffer::GL0bIndexBuffer() : GL0bVertexBuffer()
{
	mType = GL_ELEMENT_ARRAY_BUFFER;
	bind();
}

GL0bIndexBuffer::~GL0bIndexBuffer()
{
}

void GL0bIndexBuffer::update()
{
	if (!data.empty()) {
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * data.size(), &data[0], GL_STATIC_DRAW);
	}
}

void GL0bIndexBuffer::push(const unsigned int& index)
{
	data.push_back(index);
}

void GL0bIndexBuffer::push(const std::vector<unsigned int>& indices)
{
	std::copy(indices.begin(), indices.end(), std::back_inserter(data));
}
