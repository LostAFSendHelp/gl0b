#include "GL0bVertexArray.h"

GL0bVertexArray::GL0bVertexArray(bool bind)
{
    glGenVertexArrays(1, &mID);
    if (bind) {
        this->bind();
    }

	mTranslation = glm::translate(glm::mat4{ 1.0f }, glm::vec3{ .0f, .0f, .0f });
	mRotation = glm::rotate(glm::mat4{ 1.0f }, .0f, glm::vec3{ .0f, .0f, 1.0f });
}

GL0bVertexArray::~GL0bVertexArray()
{
}

void GL0bVertexArray::bind() const
{
    glBindVertexArray(mID);
}

void GL0bVertexArray::unbind() const
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

const GL0bArrayBuffer& GL0bVertexArray::arrayBuffer() const
{
    return mArrayBuffer;
}

const GL0bIndexBuffer& GL0bVertexArray::indexBuffer() const
{
    return mIndexBuffer;
}

template<>
void GL0bVertexArray::genBuffer<GL0bArrayBuffer>() {
	mArrayBuffer = GL0bArrayBuffer();
}

template<>
void GL0bVertexArray::genBuffer<GL0bIndexBuffer>() {
	mIndexBuffer = GL0bIndexBuffer();
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

void GL0bVertexArray::translate(const glm::vec3& translation) {
	mTranslation = glm::translate(mTranslation, translation);
}

void GL0bVertexArray::rotate(const float& angle, const glm::vec3& axis) {
	mRotation = glm::rotate(mRotation, angle, axis);
}

const glm::mat4& GL0bVertexArray::translation() const {
	return mTranslation;
}

const glm::mat4& GL0bVertexArray::rotation() const {
	return mRotation;
}