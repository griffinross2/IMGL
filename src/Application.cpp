#include "Application.h"

#include <iostream>
#include <string>

static OpenGLGui::Application* s_instance = nullptr;

OpenGLGui::Application::Application() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    glfwWindow = glfwCreateWindow(800, 600, "Untitled Window", NULL, NULL);
    glfwMakeContextCurrent(glfwWindow);
    gladLoadGL(glfwGetProcAddress);

    s_instance = this;
}

OpenGLGui::Application::~Application() {
    glfwTerminate();
}

void OpenGLGui::Application::setWindowTitle(const char* title) {
    if (s_instance->glfwWindow) {
        glfwSetWindowTitle(s_instance->glfwWindow, title);
    }
}

bool OpenGLGui::Application::shouldClose() {
    return glfwWindowShouldClose(s_instance->glfwWindow);
}

void OpenGLGui::Application::draw() {
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

unsigned int OpenGLGui::Application::height() {
    int height;
    glfwGetFramebufferSize(s_instance->glfwWindow, nullptr, &height);
    return static_cast<unsigned int>(height);
}

unsigned int OpenGLGui::Application::width() {
    int width;
    glfwGetFramebufferSize(s_instance->glfwWindow, &width, nullptr);
    return static_cast<unsigned int>(width);
}

OpenGLGui::Application* OpenGLGui::Application::getInstance() {
    return s_instance;
}