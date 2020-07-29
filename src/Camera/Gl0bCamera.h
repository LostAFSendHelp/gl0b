#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GL0bCamera {
public:
    GL0bCamera(const glm::vec3&);
    ~GL0bCamera();

    void hShift(const float&);
    void fShift(const float&);
    void rotate(const float&, const glm::vec3&);
    glm::mat4 view();
private:
    glm::vec3 mOrigin;
    glm::vec3 mFront { .0f, .0f, -1.0f };
    glm::vec3 mRight { 1.0f, .0f, .0f };
};