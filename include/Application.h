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
    static double deltaTime();

    static Application* getInstance();
	static GLFWwindow* getWindow();

private:
    void handleInput();

    double m_lastTime;
    double m_deltaTime;
    ShaderManager m_shaderManager;
    GLFWwindow* m_glfwWindow = nullptr;
    std::unique_ptr<Renderer> m_renderer;
};

}