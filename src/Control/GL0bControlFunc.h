#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>
#include <vector>

class GL0bControlFunc {
public:
    GL0bControlFunc(const int&, const int&, const float&, const std::function<void(float)>&);
    ~GL0bControlFunc();

    void poll(GLFWwindow*) const;
private:
    std::function<void(float)> mFunc;
    int mPositive;
    int mNegative;
    float mMagnitude;
};