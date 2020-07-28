#include "GL0bControlFunc.h"

GL0bControlFunc::GL0bControlFunc(const std::vector<int>& positive, const std::vector<int>& negative, const std::function<void()>& func)
: mFunc(func), mPositive(positive), mNegative(negative) { }

GL0bControlFunc::~GL0bControlFunc() {
    
}

void GL0bControlFunc::poll(GLFWwindow* window) const {
    auto pos = 1;
    for (const auto& key : mPositive) {
        pos *= glfwGetKey(window, key);
    }

    auto neg = 1;
    for (const auto& key : mNegative) {
        neg *= glfwGetKey(window, key);
    }

    auto magnitude = pos - neg;
    if (magnitude != 0) {
        mFunc();
    }
}