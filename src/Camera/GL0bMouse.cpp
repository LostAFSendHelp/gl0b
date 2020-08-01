#include "GL0bMouse.h"

GL0bMouse::GL0bMouse(const double& x, const double& y):
    mLocation({ x, y }),
    mLastLocation({ x, y }) { }

GL0bMouse::~GL0bMouse() { }

void GL0bMouse::update(const double& x, const double& y) {
    mLastLocation = mLocation;
    mLocation.x = x;
    mLocation.y = y;
}

void GL0bMouse::reset(const glm::vec2& location) {
    mLocation = location;
    mLastLocation = location;
}

glm::vec2 GL0bMouse::location() {
    return mLocation;
}

glm::vec2 GL0bMouse::offset() {
    return { mLocation.x - mLastLocation.x, mLastLocation.y - mLocation.y };
}