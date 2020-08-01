#include "Gl0bCamera.h"
#include <math.h>
#include <iostream>

GL0bCamera::GL0bCamera(const glm::vec3& origin, const glm::vec3& target):
    mOrigin(origin),
    mTarget(target),
    mMoveSpeed(.005f),
    mSensitivity(.02f),
    mPitch(.0f),
    mYaw(-90.0f),
    mMouse(.0, .0) { }

GL0bCamera::~GL0bCamera() { }

void GL0bCamera::hShift(const float& horizontal) {
    mOrigin += glm::normalize(glm::cross(mFront, mUp)) * horizontal;
}

void GL0bCamera::fShift(const float& face) {
    if (mGrounded) {
        mOrigin += glm::vec3{ mFront.x, .0f, mFront.z} * face;
    } else {
        mOrigin += mFront * face;
    }
}

void GL0bCamera::aim(const glm::vec3& target) {
    if (target != mOrigin) {
        mTarget = target;
    }
}

void GL0bCamera::lock(bool locked) {
    mLocked = locked;
}

void GL0bCamera::ground(bool grounded) {
    mGrounded = grounded;
}

glm::mat4 GL0bCamera::view() {
    auto target = mLocked ? mTarget : mOrigin + mFront;
    return glm::lookAt(mOrigin, target, mUp);
}

void GL0bCamera::setInput(const std::pair<int, int>& h, const std::pair<int, int>& v) {
    mHorizontal = h;
    mVertical = v;
}

void GL0bCamera::poll(GLFWwindow* window) {
    auto h = glfwGetKey(window, mHorizontal.first) - glfwGetKey(window, mHorizontal.second);
    auto v = glfwGetKey(window, mVertical.first) - glfwGetKey(window, mVertical.second);

    hShift(h * mMoveSpeed);
    fShift(v * mMoveSpeed);
}

void GL0bCamera::update(const double& x, const double& y) {
    mMouse.update(x, y);
    mYaw += mMouse.offset().x * mSensitivity;
    mPitch += mMouse.offset().y * mSensitivity;

    mPitch = glm::clamp(mPitch, -89.0f, 89.0f);

    glm::vec3 direction = {
        cosf(glm::radians(mYaw)) * cosf(glm::radians(mPitch)),
        sinf(glm::radians(mPitch)),
        sinf(glm::radians(mYaw)) * cosf(glm::radians(mPitch))
    };

    mFront = glm::normalize(direction);
}