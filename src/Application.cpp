#include "Application.h"

#include <iostream>

static OpenGLGui::Application* s_instance = nullptr;

OpenGLGui::Application::Application() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    s_instance = this;
}

OpenGLGui::Application::~Application() {
    glfwTerminate();
}

int OpenGLGui::Application::run() {
    double lastTime = glfwGetTime();

    // Check if main window is open
    while (!glfwWindowShouldClose(mainWindow->getGLFWwindow())) {
        for (auto window : windows) {
            glfwMakeContextCurrent(window);
            if (glfwWindowShouldClose(window)) {
                continue;
            }
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        std::cout << deltaTime * 1000.0 << " ms" << std::endl;
    }
    return 0;
}


OpenGLGui::Application* OpenGLGui::Application::getInstance() {
    return s_instance;
}