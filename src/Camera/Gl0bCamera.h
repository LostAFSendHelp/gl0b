#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <map>
#include "GL0bMouse.h"

class GL0bCamera {
public:
    GL0bCamera(const glm::vec3&, const glm::vec3&);
    ~GL0bCamera();

    void hShift(const float&);
    void fShift(const float&);
    void aim(const glm::vec3&);
    void lock(bool);
    void ground(bool);
    void poll(GLFWwindow* window);
    void update(const double&, const double&);
    void setInput(const std::pair<int, int>& h, const std::pair<int, int>& v);
    glm::mat4 view();

    float mMoveSpeed;
    float mSensitivity;
    GL0bMouse mMouse;

private:
    glm::vec3 mOrigin;
    glm::vec3 mFront { .0f, .0f, -1.0f };
    glm::vec3 mUp { .0f, 1.0f, .0f };
    glm::vec3 mTarget { .0f, .0f, .0f };
    bool mLocked = false;
    bool mGrounded = false;

    std::pair<int, int> mHorizontal;
    std::pair<int, int> mVertical;

    float mPitch;
    float mYaw;
};