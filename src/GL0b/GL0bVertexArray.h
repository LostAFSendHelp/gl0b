#pragma once
#include "GL0bArrayBuffer.h"
#include "GL0bIndexBuffer.h"

class GL0bVertexArray {
public:
	GL0bVertexArray(bool bind);
	~GL0bVertexArray();

	void bind();
	void unbind();
	void update();
	template<typename T> void genBuffer();
	template<typename T> void push(const T& arg, bool update);

	const unsigned int& id();
	const GL0bArrayBuffer& arrayBuffer();
	const GL0bIndexBuffer& indexBuffer();

	// TODO: deprecate this method
	void rotateArrayBuffer(const Vector3& center, const float& angle);
	void shiftArrayBuffer(const float& h, const float& v);

private:
	GL0bArrayBuffer mArrayBuffer;
	GL0bIndexBuffer mIndexBuffer;
	unsigned int mID;
};

template<>
void GL0bVertexArray::genBuffer<GL0bArrayBuffer>();

template<>
void GL0bVertexArray::genBuffer<GL0bIndexBuffer>();

template<>
void GL0bVertexArray::push<Point>(const Point& arg, bool update);

template<>
void GL0bVertexArray::push<std::vector<Point>>(const std::vector<Point>& arg, bool update);

template<>
void GL0bVertexArray::push<unsigned int>(const unsigned int& arg, bool update);

template<>
void GL0bVertexArray::push<std::vector<unsigned int>>(const std::vector<unsigned int>& arg, bool update);