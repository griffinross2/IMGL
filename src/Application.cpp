#include "Application.h"

#include <iostream>
#include <string>

static IMGL::Application* s_instance = nullptr;

IMGL::Application::Application() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    glfwWindow = glfwCreateWindow(800, 600, "Untitled Window", NULL, NULL);
    glfwMakeContextCurrent(glfwWindow);
    gladLoadGL(glfwGetProcAddress);

    s_instance = this;
}

IMGL::Application::~Application() {
    glfwTerminate();
}

void IMGL::Application::setWindowTitle(const char* title) {
    if (s_instance->glfwWindow) {
        glfwSetWindowTitle(s_instance->glfwWindow, title);
    }
}

bool IMGL::Application::shouldClose() {
    return glfwWindowShouldClose(s_instance->glfwWindow);
}

void IMGL::Application::draw() {
    // Update window
    glfwPollEvents();
    glfwMakeContextCurrent(s_instance->glfwWindow);
    
    // Update viewport
    int width, height;
    glfwGetFramebufferSize(s_instance->glfwWindow, &width, &height);
    glViewport(0, 0, width, height);

    // Clear screen
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render the GUI

    glfwSwapBuffers(s_instance->glfwWindow);
    
}

unsigned int IMGL::Application::height() {
    int height;
    glfwGetFramebufferSize(s_instance->glfwWindow, nullptr, &height);
    return static_cast<unsigned int>(height);
}

unsigned int IMGL::Application::width() {
    int width;
    glfwGetFramebufferSize(s_instance->glfwWindow, &width, nullptr);
    return static_cast<unsigned int>(width);
}

IMGL::Application* IMGL::Application::getInstance() {
    return s_instance;
}