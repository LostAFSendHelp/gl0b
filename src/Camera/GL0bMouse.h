#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class GL0bMouse {
public:
    GL0bMouse(const double&, const double&);
    ~GL0bMouse();
    
    void update(const double&, const double&);
    void reset(const glm::vec2&);
    glm::vec2 location();
    glm::vec2 offset();

private:
    glm::vec2 mLocation;
    glm::vec2 mLastLocation;
};