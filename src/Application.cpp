#include "Application.h"

#include <iostream>
#include <string>

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
    int frameCount = 0;

    // Check if main window is open
    while (!glfwWindowShouldClose(mainWindow->getGLFWwindow())) {
        for (Window* window : windows) {
			// Hide the window if it should be closed
            if (glfwWindowShouldClose(window->getGLFWwindow())) {
                window->hide();
                continue;
			}

			// Update the remaining windows
            glfwMakeContextCurrent(window->getGLFWwindow());

            window->getGladContext()->Clear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(window->getGLFWwindow());
            
        }
        glfwPollEvents();
        frameCount++;

        if (glfwGetTime() - lastTime >= 1.0) {
            mainWindow->setWindowTitle(
                ("FPS: " + std::to_string(frameCount)).c_str()
            );
            frameCount = 0;
            lastTime = glfwGetTime();
        }
    }
    return 0;
}


OpenGLGui::Application* OpenGLGui::Application::getInstance() {
    return s_instance;
}