#pragma once

#include <GLFW/glfw3.h>

namespace OpenGLGui {

class Window {
public:
    Window();
    ~Window();

    void setWindowTitle(const char* title);
    GLFWwindow* getGLFWwindow() const { return window; }

private:
    GLFWwindow* window;
};

}