#pragma once

#include "Window.h"
#include "MainWindow.h"

#include <vector>

#include <glad/gl.h>
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
        windows.push_back(window);
    }

    int run();
    static Application* getInstance();

private:
    MainWindow* mainWindow = nullptr;
    std::vector<Window*> windows;
};

}