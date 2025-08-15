#pragma once

#include "Render.h"
#include "Shader.h"

#include <vector>
#include <memory>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace IMGL {

class Application {
public:
    Application();
    ~Application();

    static void setWindowTitle(const char* title);
    static void setWindowSize(unsigned int width, unsigned int height);
    static bool shouldClose();
    static void draw();
    static unsigned int height();
    static unsigned int width();

    static Application* getInstance();

private:
    ShaderManager shaderManager;
    GLFWwindow* glfwWindow = nullptr;
    std::unique_ptr<Renderer> renderer;
};

}