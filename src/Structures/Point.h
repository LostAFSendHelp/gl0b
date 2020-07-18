#pragma once
#include "Vector3.h"

struct Point {
	Vector3 mPosition;
	Vector3 mColor;

	void rotateSelf(const Vector3& center, const float angle);
	Point rotateNew(const Vector3& center, const float angle);
};