#include "Application.h"

OpenGLGui::Application::Application() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    window = glfwCreateWindow(800, 600, "Untitled Application", NULL, NULL);
    glfwMakeContextCurrent(window);
}

OpenGLGui::Application::~Application() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

int OpenGLGui::Application::run() {
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}

void OpenGLGui::Application::setWindowTitle(const char* title) {
    glfwSetWindowTitle(window, title);
}