#pragma once

#include <GLFW/glfw3.h>

namespace OpenGLGui {

class Application {
public:
    Application();
    ~Application();

    int run();
    void setWindowTitle(const char* title);

private:
    GLFWwindow* window;
};

}