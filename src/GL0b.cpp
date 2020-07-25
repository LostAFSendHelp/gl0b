#include <iostream>
#include <conio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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
    
    auto hMultiplier = glfwGetKey(window, GLFW_KEY_RIGHT) - glfwGetKey(window, GLFW_KEY_LEFT);
    horizontal(hMultiplier * .002f);

    auto vMultiplier = glfwGetKey(window, GLFW_KEY_UP) - glfwGetKey(window, GLFW_KEY_DOWN);
    vertical(vMultiplier * .002f);
    
    rotate(glfwGetKey(window, GLFW_KEY_SPACE) * 0.005f);

    glfwSetWindowShouldClose(window, glfwGetKey(window, GLFW_KEY_Q));
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
        {-.5f, .5f, .0f, 0.0f, 0.0f, 1.0f },    // TLF
        { .5f, .5f, .0f, 1.0f, 0.0f, 0.0f },     // TRF
        { .5f, -.5f, .0f, 1.0f, 1.0f, 0.0f},    // BRF
        {-.5f, -.5f, .0f, 0.0f, 1.0f, 0.0f},    // BLF
        
        {-.5f, .5f, -1.0f, 0.0f, 0.0f, 1.0f },    // TLB
        { .5f, .5f, -1.0f, 1.0f, 0.0f, 0.0f },     // TRB
        { .5f, -.5f, -1.0f, 1.0f, 1.0f, 0.0f},    // BRB
        {-.5f, -.5f, -1.0f, 0.0f, 1.0f, 0.0f}    // BLB
    };

    const std::vector<unsigned int> indices = {
        // front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
    };

    auto vertexArray = GL0bVertexArray(true);
    vertexArray.genBuffer<GL0bArrayBuffer>();
    vertexArray.genBuffer<GL0bIndexBuffer>();
    vertexArray.push(vertices, true);
    vertexArray.push(indices, true);
    vertexArray.unbind();

    // -------------------------------------------

    auto program = GL0bProgram();
    program.addShader(GL_VERTEX_SHADER, "src/resources/shaders/vertex_shader.glsl");
    program.addShader(GL_FRAGMENT_SHADER, "src/resources/shaders/fragment_shader.glsl");
    program.link();
    program.use();

    auto rotation = glm::mat4 { 1.0f };
    auto translation = glm::mat4 { 1.0f };

    auto model = glm::rotate(glm::mat4{ 1.0f }, glm::radians(-45.0f), glm::vec3(1.0f, .0f, .0f));
    auto view = glm::translate(glm::mat4{ 1.0f }, glm::vec3(.0f, .0f, -3.0f));
    auto projection = glm::perspective(glm::radians(45.0f), 600.0f/ 600.0f, .1f, 100.0f);

    program.setUniformMat4("model", model);
    program.setUniformMat4("view", view);
    program.setUniformMat4("projection", projection);

    vertexArray.bind(); // Needs to be moved to render loop if multiple arrays are to be drawn

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();

        pollKey(window,
        [&](float h) {
            translation = glm::translate(translation, glm::vec3{ h, .0f, .0f });
        },
        [&](float v) {
            translation = glm::translate(translation, glm::vec3{ .0f, v, .0f });
        },
        [&](float a) {
            rotation = glm::rotate(rotation, a, glm::vec3{ 0, 0, 1.0f });
        });

        program.setUniformMat4("rotation", rotation);
        program.setUniformMat4("translation", translation);

        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
    }

    program.dispose();

    glfwTerminate();
    return 0;
}
