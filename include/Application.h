#pragma once

#include "Window.h"
#include "MainWindow.h"

#include <vector>

#include <GLFW/glfw3.h>

namespace OpenGLGui {
    
class Application {
public:
Application();
    ~Application();

    void setMainWindow(MainWindow *window) {
        mainWindow = window;
    }

    void addWindow(Window *window) {
        windows.push_back(window->getGLFWwindow());
    }

    int run();
    static Application* getInstance();

private:
    MainWindow* mainWindow = nullptr;
    std::vector<GLFWwindow*> windows;
};

}