#include "Window.h"
#include "Application.h"

OpenGLGui::Window::Window() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    window = glfwCreateWindow(800, 600, "Untitled Window", NULL, NULL);
    glfwMakeContextCurrent(window);
    // glfwSwapInterval(0);

    gladContext = (GladGLContext*) calloc(1, sizeof(GladGLContext));
    if (!gladContext) throw std::runtime_error("Failed to allocate memory for GladGLContext");
    gladLoadGLContext(gladContext, glfwGetProcAddress);

    OpenGLGui::Application::getInstance()->addWindow(this);
}

OpenGLGui::Window::~Window() {
    glfwDestroyWindow(window);
}

void OpenGLGui::Window::setWindowTitle(const char* title) {
    glfwSetWindowTitle(window, title);
}