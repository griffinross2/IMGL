#pragma once

#include <vector>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace OpenGLGui {

class Application {
public:
    Application();
    ~Application();

    static void setWindowTitle(const char* title);
    static bool shouldClose();
    static void draw();
    static unsigned int height();
    static unsigned int width();

    static Application* getInstance();

private:
    GLFWwindow* glfwWindow = nullptr;
};

}