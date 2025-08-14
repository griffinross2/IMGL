#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace OpenGLGui {

class Window {
public:
    Window(Window* parent = nullptr);
    ~Window();

    void setWindowTitle(const char* title);
    void hide();
	void show();
    GLFWwindow* getGLFWwindow() const { return window; }
    GladGLContext* getGladContext() const { return gladContext; }

private:
    GladGLContext* gladContext = nullptr;
    GLFWwindow* window;
};

}