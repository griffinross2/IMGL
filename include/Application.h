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
	static float hscale();
	static float vscale();
    static double deltaTime();

    static Application* getInstance();
	static GLFWwindow* getWindow();

private:
    void handleInput();

	unsigned int m_width = 0;
	unsigned int m_height = 0;
	float m_hscale = 1.0f;
	float m_vscale = 1.0f;
    double m_lastTime;
    double m_deltaTime;
    ShaderManager m_shaderManager;
    GLFWwindow* m_glfwWindow = nullptr;
    std::unique_ptr<Renderer> m_renderer;
};

}