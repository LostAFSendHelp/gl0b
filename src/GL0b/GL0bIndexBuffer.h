#pragma once
#include <vector>
#include "GL0bVertexBuffer.h"

class GL0bIndexBuffer : public GL0bVertexBuffer {
public:
	GL0bIndexBuffer();
	~GL0bIndexBuffer();

	void update() override;
	void push(const unsigned int& index);
	void push(const std::vector<unsigned int>& indices);

	unsigned int indexCount() const;

private:
	std::vector<int> mData;
};