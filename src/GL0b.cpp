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
#include "Control/GL0bCentralControl.h"
#include "Camera/Gl0bCamera.h"
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

int main()
{
    // Init context
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

    // Init vertices, indices & vertex arrays
    const std::vector<Point> vertices = gl0b::generate_vertex_samples();
    const std::vector<unsigned int> indices = gl0b::generate_index_samples();

    const auto sampleVA = gl0b::generate_va_sample(vertices, indices);
    auto vertexArrays = std::vector<GL0bVertexArray>{ sampleVA, sampleVA };

    vertexArrays[0].translate({ -.5f, .0f, .0f });
    vertexArrays[1].translate({ .5f, .0f, .0f });

    // Init program
    auto program = GL0bProgram();
    program.addShader(GL_VERTEX_SHADER, "src/resources/shaders/vertex_shader.glsl");
    program.addShader(GL_FRAGMENT_SHADER, "src/resources/shaders/fragment_shader.glsl");
    program.link();
    program.use();

    auto renderer = GL0bRenderer(program);

    auto model = glm::rotate(glm::mat4{ 1.0f }, glm::radians(-60.0f), glm::vec3{ 1.0f, .0f, .0f });
    auto projection = glm::perspective(glm::radians(45.0f), 1.0f, .1f, 100.0f);

    program.setUniformMat4("projection", projection);

    vertexArrays[0].unbind();
    vertexArrays[1].unbind();

    // Init camera
    auto camera = GL0bCamera({ .0f, .0f, 3.0f });

    // Init control
    auto control = GL0bCentralControl();    
    control
        .push({ GLFW_KEY_Z, GLFW_KEY_X, .005f, [&](float m){
            vertexArrays[0].rotate(m, { .0f, .0f, 1.0f });
        } })
        .push({ GLFW_KEY_C, GLFW_KEY_V, .005f, [&](float m){
            vertexArrays[1].rotate(m, { .0f, .0f, 1.0f });
        } })
        .push({ GLFW_KEY_RIGHT, GLFW_KEY_LEFT, .005f, [&](float m){
            model = glm::translate(model, glm::vec3{ m, .0f, .0f });
        } })
        .push({ GLFW_KEY_UP, GLFW_KEY_DOWN, .005f, [&](float m){
            model = glm::translate(model, glm::vec3{ .0f, m, .0f });
        } })
        .push({ GLFW_KEY_D, GLFW_KEY_A, .005f, [&](float m){
            camera.hShift(m);
        } })
        .push({ GLFW_KEY_W, GLFW_KEY_S, .005f, [&](float m){
            camera.fShift(m);
        } })
        .push({ GLFW_KEY_Q, GLFW_KEY_Q, 1.0f, [&](float m){
            glfwSetWindowShouldClose(window, (int)m);
        } });
    
    glEnable(GL_DEPTH_TEST);
    
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();

        renderer.clear();

        // TODO: perform control here
        control.poll(window);

        program.setUniformMat4("model", model);
        program.setUniformMat4("view", camera.view());

        for (const auto& va : vertexArrays) {
            renderer.drawElements(va);
        }
    }

    program.dispose();

    glfwTerminate();
    return 0;
}
