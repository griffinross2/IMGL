#include "Application.h"

#include "Container.h"
#include "Text.h"
#include "Input.h"

#include <iostream>
#include <string>
#include <memory>

namespace IMGL {

static Application* s_instance = nullptr;

Application::Application() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    m_glfwWindow = glfwCreateWindow(800, 600, "Untitled Window", NULL, NULL);
    glfwMakeContextCurrent(m_glfwWindow);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);
    glfwSetInputMode(m_glfwWindow, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

    // Load Shaders
    ShaderManager::get()->addShader("triangle", "shaders/tri.vert", "shaders/tri.frag");
    ShaderManager::get()->addShader("text", "shaders/text.vert", "shaders/text.frag");

    FreeTypeInit();
    m_renderer = std::make_unique<Renderer>();

	// Register global key callback
	glfwSetKeyCallback(m_glfwWindow, KeyEventCallback);
	glfwSetCharCallback(m_glfwWindow, CharEventCallback);

    m_lastTime = glfwGetTime();
    m_deltaTime = 0.0;

    s_instance = this;
}

Application::~Application() {
    Renderer::Destroy();
    DestroyFontCache();
	FreeTypeDone();
    glfwTerminate();
}

void Application::setWindowTitle(const char* title) {
    if (s_instance->m_glfwWindow) {
        glfwSetWindowTitle(s_instance->m_glfwWindow, title);
    }
}

void Application::setWindowSize(unsigned int width, unsigned int height) {
    if (s_instance->m_glfwWindow) {
        glfwSetWindowSize(s_instance->m_glfwWindow, static_cast<int>(width), static_cast<int>(height));
    }
}

bool Application::shouldClose() {
    return glfwWindowShouldClose(s_instance->m_glfwWindow);
}

void Application::draw() {
    // Update window
    glfwMakeContextCurrent(s_instance->m_glfwWindow);
    glfwPollEvents();
    
    // Update viewport
    int width, height;
    glfwGetFramebufferSize(s_instance->m_glfwWindow, &width, &height);
    glViewport(0, 0, width, height);

    // Clear screen
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Delta time
    double currentTime = glfwGetTime();
    s_instance->m_deltaTime = currentTime - s_instance->m_lastTime;
    s_instance->m_lastTime = currentTime;

    // Handle input
    ProcessInput();

    // Set the cursor shape then reset the recorded state
    CursorShape currentCursorShape = GetCursorShape();
    glfwSetCursor(s_instance->m_glfwWindow, glfwCreateStandardCursor(static_cast<int>(currentCursorShape)));
    SetCursorShape(CURSOR_ARROW);

    // Render the GUI
    Renderer::Render();

    glfwSwapBuffers(s_instance->m_glfwWindow);

}

unsigned int Application::height() {
    int height;
    glfwGetFramebufferSize(s_instance->m_glfwWindow, nullptr, &height);
    return static_cast<unsigned int>(height);
}

unsigned int Application::width() {
    int width;
    glfwGetFramebufferSize(s_instance->m_glfwWindow, &width, nullptr);
    return static_cast<unsigned int>(width);
}

Application* Application::getInstance() {
    return s_instance;
}

GLFWwindow* Application::getWindow() {
    return s_instance->m_glfwWindow;
}

double Application::deltaTime() {
    return s_instance->m_deltaTime;
}

}