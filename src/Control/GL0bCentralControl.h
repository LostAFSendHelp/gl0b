#pragma once
#include <vector>
#include <functional>
#include <GLFW/glfw3.h>
#include "GL0bControlFunc.h"

class GL0bCentralControl {
public:
    void poll(GLFWwindow*) const;
    GL0bCentralControl& push(const GL0bControlFunc&);
private:
    std::vector<GL0bControlFunc> mFuncs;
};