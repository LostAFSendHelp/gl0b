#include "GL0bCentralControl.h"

void GL0bCentralControl::poll(GLFWwindow* window) const {
    for (const auto& func : mFuncs) {
        func.poll(window);
    }
}

GL0bCentralControl& GL0bCentralControl::push(const GL0bControlFunc& func) {
    mFuncs.push_back(func);
    return *this;
}
