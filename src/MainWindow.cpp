#include "MainWindow.h"
#include "Application.h"

OpenGLGui::MainWindow::MainWindow() : Window() {
    OpenGLGui::Application::getInstance()->setMainWindow(this);
}
