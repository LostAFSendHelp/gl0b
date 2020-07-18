#include <iostream>
#include <conio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include "Progam/GL0bProgram.h"
#include "Structures/Point.h"
#include "GL0b/GL0bVertexArray.h"

#define GL0BTERMINATE(x) std::cout << x << std::endl; _getch(); return 0
#define GL0B_WIDTH 800
#define GL0B_HEIGHT 600

static void gl0bViewPort(const GLint& width, const GLint& height) {
    auto edge = std::min<GLint>(width, height);
    auto offset = (width - height) / 2;
    if (offset > 0) {
        glViewport(offset, 0, edge, edge);
    }
    else {
        glViewport(0, abs(offset), edge, edge);
    }
}

static void pollKey(GLFWwindow* window,
    const std::function<void(float)>& horizontal,
    const std::function<void(float)>& vertical,
    const std::function<void(float)>& rotate) {
    if (glfwGetKey(window, GLFW_KEY_Q)) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT)) {
        horizontal(-0.001f);
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
        horizontal(0.001f);
    }

    if (glfwGetKey(window, GLFW_KEY_UP)) {
        vertical(0.001f);
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN)) {
        vertical(-0.001f);
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE)) {
        rotate(0.0012f);
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    auto window = glfwCreateWindow(GL0B_WIDTH, GL0B_HEIGHT, "One step back", NULL, NULL);

    if (!window) {
        GL0BTERMINATE("Error creating window");
    }

    glfwMakeContextCurrent(window);

    glewInit();

    gl0bViewPort(GL0B_WIDTH, GL0B_HEIGHT);

    glfwSetFramebufferSizeCallback(window, [] (GLFWwindow* w, int width, int height) {
        static unsigned int count = 1;
        std::cout << "resizing frame buffer " << count++ << std::endl;
        gl0bViewPort(width, height);
    });

    // TODO: delete dis
    const std::vector<Point> vertices = {
        { 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f },     // TR
        { 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f},    // BR
        {-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f },    // TL
        {-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f}    // BL
    };

    std::vector<Point> rotatedVertices{};
    for (auto vertex : vertices) {
        rotatedVertices.push_back(vertex.rotateNew({ 0,0,0 }, 1.57f / 2));
    }

    const std::vector<unsigned int> indices = {
        1, 0, 2,
        3, 1, 2
    };

    auto vertexArray = GL0bVertexArray(true);
    vertexArray.genBuffer<GL0bArrayBuffer>();
    vertexArray.genBuffer<GL0bIndexBuffer>();
    vertexArray.push(vertices, true);
    vertexArray.push(indices, true);
    vertexArray.unbind();

    // -------------------------------------------

    auto program = GL0bProgram();
    program.addShader(GL_VERTEX_SHADER, "../src/resources/shaders/vertex_shader.glsl");
    program.addShader(GL_FRAGMENT_SHADER, "../src/resources/shaders/fragment_shader.glsl");
    program.link();
    program.use();

    Vector3 center{ 0, 0, 0 };
    vertexArray.bind();

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();

        pollKey(window, [&](float h) {
            //center.shift(h, 0);
            vertexArray.shiftArrayBuffer(h, 0);
        }, [&](float v) {
            //center.shift(0, v);
            vertexArray.shiftArrayBuffer(0, v);
        }, [&](float angle) {
            vertexArray.rotateArrayBuffer(center, angle);
        });

        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    program.dispose();

    glfwTerminate();

    std::cout << "Press any key to continue..." << std::endl;
    _getch();
}
