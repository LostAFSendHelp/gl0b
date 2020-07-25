#include "GL0bVertexArray.h"

GL0bVertexArray::GL0bVertexArray(bool bind)
{
    glGenVertexArrays(1, &mID);
    if (bind) {
        this->bind();
    }
}

GL0bVertexArray::~GL0bVertexArray()
{
}

void GL0bVertexArray::bind()
{
    glBindVertexArray(mID);
}

void GL0bVertexArray::unbind()
{
    glBindVertexArray(0);
}

void GL0bVertexArray::update()
{
    mArrayBuffer.update();
    mIndexBuffer.update();
}

const unsigned int& GL0bVertexArray::id()
{
    return mID;
}

const GL0bArrayBuffer& GL0bVertexArray::arrayBuffer()
{
    return mArrayBuffer;
}

const GL0bIndexBuffer& GL0bVertexArray::indexBuffer()
{
    return mIndexBuffer;
}

void GL0bVertexArray::rotateArrayBuffer(const Vector3& center, const float& angle)
{
	bind();
	mArrayBuffer.rotate(center, angle);
	mArrayBuffer.update();
}

void GL0bVertexArray::shiftArrayBuffer(const float& h, const float& v)
{
	bind();
	mArrayBuffer.shift(h, v);
	mArrayBuffer.update();
}

template<typename T>
void GL0bVertexArray::genBuffer() {
	static_assert(false);
}

template<>
void GL0bVertexArray::genBuffer<GL0bArrayBuffer>() {
	mArrayBuffer = GL0bArrayBuffer();
}

template<>
void GL0bVertexArray::genBuffer<GL0bIndexBuffer>() {
	mIndexBuffer = GL0bIndexBuffer();
}

template<typename T>
void GL0bVertexArray::push(const T&, bool update) {
	static_assert(false);
}

template<>
void GL0bVertexArray::push<Point>(const Point& arg, bool update) {
	mArrayBuffer.push(arg);
	if (update) {
		mArrayBuffer.update();
	}
}

template<>
void GL0bVertexArray::push<std::vector<Point>>(const std::vector<Point>& arg, bool update) {
	mArrayBuffer.push(arg);
	if (update) {
		mArrayBuffer.update();
	}
}

template<>
void GL0bVertexArray::push<unsigned int>(const unsigned int& arg, bool update) {
	mIndexBuffer.push(arg);
	if (update) {
		mIndexBuffer.update();
	}
}

template<>
void GL0bVertexArray::push<std::vector<unsigned int>>(const std::vector<unsigned int>& arg, bool update) {
	mIndexBuffer.push(arg);
	if (update) {
		mIndexBuffer.update();
	}
}