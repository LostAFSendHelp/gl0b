#include "Point.h"
#include <cmath>

// TODO: implement necessary transformations

void Point::rotateSelf(const Vector3& center, const float angle)
{
    float& x = mPosition.mX;
    float& y = mPosition.mY;
    x = (x - center.mX) * cosf(angle) - (y - center.mY) * sinf(angle);
    y = (x - center.mX) * sinf(angle) + (y - center.mY) * cosf(angle);
}

Point Point::rotateNew(const Vector3& center, const float angle)
{
    const float x = mPosition.mX;
    const float y = mPosition.mY;
    
    return Point{
        (x - center.mX)* cosf(angle) - (y - center.mY) * sinf(angle),
        (x - center.mX)* sinf(angle) + (y - center.mY) * cosf(angle),
        mPosition.mZ,
        mColor.mX,
        mColor.mY,
        mColor.mZ
    };
}
