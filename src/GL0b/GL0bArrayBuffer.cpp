#include "GL0bArrayBuffer.h"
#include <GL/glew.h>

GL0bArrayBuffer::GL0bArrayBuffer() : GL0bVertexBuffer()
{
	mType = GL_ARRAY_BUFFER;
	bind();
}

GL0bArrayBuffer::~GL0bArrayBuffer()
{
}

void GL0bArrayBuffer::update()
{
	if (!mData.empty()) {
		bind();
		glBufferData(mType, sizeof(float) * mData.size(), &mData[0], GL_STATIC_DRAW);
		glVertexAttribPointer(GL0B_INDEX_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, nullptr);
		glVertexAttribPointer(GL0B_INDEX_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (const void*)(sizeof(float) * 3));
		glEnableVertexAttribArray(GL0B_INDEX_POSITION);
		glEnableVertexAttribArray(GL0B_INDEX_COLOR);
	}
}

void GL0bArrayBuffer::push(const Point& point)
{
	mData.push_back(point.mPosition.mX);
	mData.push_back(point.mPosition.mY);
	mData.push_back(point.mPosition.mZ);

	mData.push_back(point.mColor.mX);
	mData.push_back(point.mColor.mY);
	mData.push_back(point.mColor.mZ);
}

void GL0bArrayBuffer::push(std::vector<Point> points)
{
	for (auto point : points) {
		push(point);
	}
}

void GL0bArrayBuffer::rotate(const Vector3& center, const float& angle)
{
	for (auto i = 0; i < mData.size(); i += 6) {
		auto x = (mData[i] - center.mX) * cosf(angle) - (mData[i + 1] - center.mY) * sinf(angle) + center.mX;
		auto y = (mData[i] - center.mX) * sinf(angle) + (mData[i + 1] - center.mY) * cosf(angle) + center.mY;

		mData[i] = x;
		mData[i + 1] = y;
	}
}

void GL0bArrayBuffer::shift(const float& h, const float& v)
{
	for (auto i = 0; i < mData.size(); i += 6) {
		mData[i] += h;
		mData[i + 1] += v;
	}
}
