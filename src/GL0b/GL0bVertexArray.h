#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GL0bArrayBuffer.h"
#include "GL0bIndexBuffer.h"

class GL0bVertexArray {
public:
	GL0bVertexArray(bool bind = false);
	~GL0bVertexArray();

	void bind() const;
	void unbind() const;
	void update();
	template<typename T> void genBuffer();
	template<typename T> void push(const T& arg, bool update);

	const unsigned int& id();
	const GL0bArrayBuffer& arrayBuffer() const;
	const GL0bIndexBuffer& indexBuffer() const;

	void translate(const glm::vec3& translation);
	void rotate(const float& angle, const glm::vec3& axis = { .0f, .0f, 1.0f });

	const glm::mat4& translation() const;
	const glm::mat4& rotation() const;

private:
	glm::mat4 mTranslation;
	glm::mat4 mRotation;
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