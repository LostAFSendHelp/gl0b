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
#include "Renderer/GL0bRenderer.h"
#include "samples/sample_instances.h"

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

// TODO: create a temporary central control
static void pollKey(GLFWwindow* window,
    const std::function<void(float)>& horizontal,
    const std::function<void(float)>& vertical,
    const std::function<void(float, float)>& rotate) {
    
    auto hMultiplier = glfwGetKey(window, GLFW_KEY_RIGHT) - glfwGetKey(window, GLFW_KEY_LEFT);
    horizontal(hMultiplier * .002f);

    auto vMultiplier = glfwGetKey(window, GLFW_KEY_UP) - glfwGetKey(window, GLFW_KEY_DOWN);
    vertical(vMultiplier * .002f);
    
    rotate(glfwGetKey(window, GLFW_KEY_Z) * 0.005f,
           glfwGetKey(window, GLFW_KEY_X) * 0.005f);

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

    const std::vector<Point> vertices = gl0b::generate_vertex_samples();
    const std::vector<unsigned int> indices = gl0b::generate_index_samples();

    const auto sampleVA = gl0b::generate_va_sample(vertices, indices);
    auto vertexArrays = std::vector<GL0bVertexArray>{ sampleVA, sampleVA };

    vertexArrays[0].translate({ -.5f, .0f, .0f });
    vertexArrays[1].translate({ .5f, .0f, .0f });

    // -------------------------------------------

    auto program = GL0bProgram();
    program.addShader(GL_VERTEX_SHADER, "src/resources/shaders/vertex_shader.glsl");
    program.addShader(GL_FRAGMENT_SHADER, "src/resources/shaders/fragment_shader.glsl");
    program.link();
    program.use();

    auto renderer = GL0bRenderer(program);

    auto model = glm::rotate(glm::mat4{ 1.0f }, glm::radians(-60.0f), glm::vec3{ 1.0f, .0f, .0f });
    auto view = glm::translate(glm::mat4{ 1.0f }, glm::vec3{ .0f, .0f, -3.0f });
    auto projection = glm::perspective(glm::radians(45.0f), 1.0f, .1f, 100.0f);

    program.setUniformMat4("view", view);
    program.setUniformMat4("projection", projection);

    vertexArrays[0].unbind();
    vertexArrays[1].unbind();

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();

        renderer.clear();

        pollKey(window,
        [&](float h) {
            model = glm::translate(model, glm::vec3{ h, .0f, .0f });
        },
        [&](float v) {
            model = glm::translate(model, glm::vec3{ .0f, v, .0f });
        },
        [&](float a, float b) {
            vertexArrays[0].rotate(a);
            vertexArrays[1].rotate(b);
        });

        program.setUniformMat4("model", model);

        for (const auto& va : vertexArrays) {
            renderer.drawElements(va);
        }
    }

    program.dispose();

    glfwTerminate();
    return 0;
}
