#include "Application.h"
#include "Window.h"
#include "MainWindow.h"

int main() {
    OpenGLGui::Application app;
    OpenGLGui::MainWindow window;
    OpenGLGui::Window dialog(&window);
    window.setWindowTitle("Basic Window Example");
    dialog.setWindowTitle("Dialog");

    return app.run();
}