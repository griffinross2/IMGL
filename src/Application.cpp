#include "Application.h"

#include "Text.h"

#include <iostream>
#include <string>

static IMGL::Application* s_instance = nullptr;

IMGL::Application::Application() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    glfwWindow = glfwCreateWindow(800, 600, "Untitled Window", NULL, NULL);
    glfwMakeContextCurrent(glfwWindow);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    // Load Shaders
    ShaderManager::get()->addShader("triangle", "shaders/tri.vert", "shaders/tri.frag");
    ShaderManager::get()->addShader("text", "shaders/text.vert", "shaders/text.frag");

    FreeTypeInit();
    renderer = std::make_unique<Renderer>();

    s_instance = this;
}

IMGL::Application::~Application() {
    Renderer::Destroy();
	FreeTypeDone();
    glfwTerminate();
}

void IMGL::Application::setWindowTitle(const char* title) {
    if (s_instance->glfwWindow) {
        glfwSetWindowTitle(s_instance->glfwWindow, title);
    }
}

void IMGL::Application::setWindowSize(unsigned int width, unsigned int height) {
    if (s_instance->glfwWindow) {
        glfwSetWindowSize(s_instance->glfwWindow, static_cast<int>(width), static_cast<int>(height));
    }
}

bool IMGL::Application::shouldClose() {
    return glfwWindowShouldClose(s_instance->glfwWindow);
}

void IMGL::Application::draw() {
    // Update window
    glfwMakeContextCurrent(s_instance->glfwWindow);
    glfwPollEvents();
    
    // Update viewport
    int width, height;
    glfwGetFramebufferSize(s_instance->glfwWindow, &width, &height);
    glViewport(0, 0, width, height);

    // Clear screen
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render the GUI
    IMGL::Renderer::Render();

    glfwSwapBuffers(s_instance->glfwWindow);
    
}

unsigned int IMGL::Application::height() {
    int height;
    glfwGetFramebufferSize(s_instance->glfwWindow, nullptr, &height);
    return static_cast<unsigned int>(height);
}

unsigned int IMGL::Application::width() {
    int width;
    glfwGetFramebufferSize(s_instance->glfwWindow, &width, nullptr);
    return static_cast<unsigned int>(width);
}

IMGL::Application* IMGL::Application::getInstance() {
    return s_instance;
}