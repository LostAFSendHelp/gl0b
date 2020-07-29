#include "Gl0bCamera.h"

GL0bCamera::GL0bCamera(const glm::vec3& origin) : mOrigin(origin) { }

GL0bCamera::~GL0bCamera() { }

void GL0bCamera::hShift(const float& horizontal) {
    mOrigin += mRight * horizontal;
}

void GL0bCamera::fShift(const float& face) {
    mOrigin += mFront * face;
}

void GL0bCamera::rotate(const float& angle, const glm::vec3& axis) {
    
}

glm::mat4 GL0bCamera::view() {
    return glm::lookAt(mOrigin, mOrigin + glm::vec3{ .0f, .0f, -3.0f }, glm::normalize(glm::cross(mRight, mFront)));
}