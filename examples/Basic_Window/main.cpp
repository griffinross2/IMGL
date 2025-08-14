#include "Application.h"

int main() {
    OpenGLGui::Application app;
    app.setWindowTitle("Basic Window Example");

    double lastTime = glfwGetTime();
    int frameCount = 0;

    // Check if main window is open
    while (!OpenGLGui::Application::shouldClose()) {
        OpenGLGui::Application::draw();

        frameCount++;
        if (glfwGetTime() - lastTime >= 1.0) {
            OpenGLGui::Application::setWindowTitle(("FPS: " + std::to_string(frameCount)).c_str());
            frameCount = 0;
            lastTime = glfwGetTime();
        }
    }

    return 0;
}