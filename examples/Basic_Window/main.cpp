#include "Application.h"

int main() {
    IMGL::Application app;
    app.setWindowTitle("Basic Window Example");

    double lastTime = glfwGetTime();
    int frameCount = 0;

    // Check if main window is open
    while (!IMGL::Application::shouldClose()) {
        IMGL::Application::draw();

        frameCount++;
        if (glfwGetTime() - lastTime >= 1.0) {
            IMGL::Application::setWindowTitle(("FPS: " + std::to_string(frameCount)).c_str());
            frameCount = 0;
            lastTime = glfwGetTime();
        }
    }

    return 0;
}