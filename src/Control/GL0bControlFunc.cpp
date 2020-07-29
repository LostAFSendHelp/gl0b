#include "GL0bControlFunc.h"

GL0bControlFunc::GL0bControlFunc(const int& positive, const int& negative, const float& magnitude, const std::function<void(float)>& func)
: mFunc(func), mPositive(positive), mNegative(negative), mMagnitude(magnitude) { }

GL0bControlFunc::~GL0bControlFunc() {
    
}

void GL0bControlFunc::poll(GLFWwindow* window) const {
    auto pos = glfwGetKey(window, mPositive);
    auto neg = glfwGetKey(window, mNegative);

    auto multiplier = (mPositive != mNegative) ? pos - neg : pos * neg;
    if (multiplier != 0) {
        mFunc(mMagnitude * multiplier);
    }
}