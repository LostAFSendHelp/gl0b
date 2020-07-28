#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>
#include <vector>

class GL0bControlFunc {
public:
    GL0bControlFunc(const std::vector<int>&, const std::vector<int>&, const std::function<void()>&);
    ~GL0bControlFunc();

    void poll(GLFWwindow*) const;
private:
    std::function<void()> mFunc;
    std::vector<int> mPositive;
    std::vector<int> mNegative;
};