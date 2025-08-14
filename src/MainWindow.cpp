#include "MainWindow.h"
#include "Application.h"

OpenGLGui::MainWindow::MainWindow() : Window(nullptr) {
    OpenGLGui::Application::getInstance()->setMainWindow(this);
}
