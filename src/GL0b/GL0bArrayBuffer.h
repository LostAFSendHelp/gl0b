#pragma once
#include <vector>
#include "GL0bVertexBuffer.h"
#include "../Structures/Point.h"

class GL0bArrayBuffer : public GL0bVertexBuffer {
public:
	GL0bArrayBuffer();
	~GL0bArrayBuffer();

	void update() override;
	void push(const Point& point);
	void push(std::vector<Point> points);
	void rotate(const Vector3& center, const float& angle);
	void shift(const float& h, const float& v);

private:
	std::vector<float> mData;
};